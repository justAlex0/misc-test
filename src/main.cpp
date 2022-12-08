#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "main.hpp"

void processPolys(const char *file, Smart_ptr<Polygon> &polygon)
{
    std::ifstream polys {file};
    assert(polys && "Couldn't open the file with polys");

    std::vector<Point2D> positions {};
    const std::string separator {','};

    // Читать файл до конца
    while (polys)
    {
        std::string coordinate;
        polys >> coordinate;
        if (coordinate.length() > 0)
        {
            // Конвертирую числовую строку в целое число
            pos x {std::stoi(coordinate.substr(0, coordinate.find(separator)))};
            pos y {std::stoi(coordinate.substr(coordinate.find(separator) + 1, coordinate.length()))};
            // Помещаю координаты в стек массива
            positions.push_back({x, y});
        }
    };

    polygon->setArrayPos(positions);
}

void processLines (const char *file, std::vector<Segment> &arrayOfSegments)
{
    std::ifstream lines {file};
    assert(lines && "Couldn't open the file with lines");

    const std::string separator {','};
    pos x1, y1, x2, y2;

    // Читать файл до конца
    while (lines)
    {
        std::string coordinate;
        lines >> coordinate;
        if (coordinate.length() > 0)
        {
            // Конвертирую числовую строку в целое число
            x1 = std::stoi(coordinate.substr(0, coordinate.find(separator)));
            y1 = std::stoi(coordinate.substr(coordinate.find(separator) + 1, coordinate.length()));

            lines >> coordinate;
            if (coordinate.length() > 0)
            {
                // Конвертирую числовую строку в целое число
                x2 = std::stoi(coordinate.substr(0, coordinate.find(separator)));
                y2 = std::stoi(coordinate.substr(coordinate.find(separator) + 1, coordinate.length()));

                // Забиваю координаты в объект
                Segment segment {x1, y1, x2, y2};
                // Объект шлю в массив
                arrayOfSegments.push_back(segment);
            }
        }
    };
}

void writeResults (const int &status, const int &line)
{
    static std::ofstream results { "results.txt" };
    assert(results && "Couldn't open the file results.txt");

    switch (status)
    {
        case 0:
            results << "[Отрезок: #" << line << "] " << "Oтрезок находится внутри многоугольника\n";
            std::cout << "[Отрезок: #" << line << "] " << "Oтрезок находится внутри многоугольника" << std::endl;
            break;
        case 1:
            results << "[Отрезок: #" << line << "] " << "Oтрезок пересекает многоугольник\n";
            std::cout << "[Отрезок: #" << line << "] " << "Oтрезок пересекает многоугольник" << std::endl;
            break;
        case 2:
            results << "[Отрезок: #" << line << "] " << "Oтрезок частично пересекает многоугольник\n";
            std::cout << "[Отрезок: #" << line << "] " << "Oтрезок частично пересекает многоугольник" << std::endl;
            break;
        case 3:
            results << "[Отрезок: #" << line << "] " << "Oтрезок не имеет ничего общего с многоугольником\n";
            std::cout << "[Отрезок: #" << line << "] " << "Oтрезок не имеет ничего общего с многоугольником" << std::endl;
            break;
        default:
            break;
    }
}

double getDistance (const pos &x1, const pos &y1, const pos &x2, const pos &y2)
{
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2));
}

bool defineRelation (const pos &x, const pos &y, const std::vector<Point2D> &coordinates)
{
    int amountOfPoints {static_cast<int>(coordinates.size())};
    double degree {0.0};
    for (int i = 0, j = amountOfPoints - 1; i < amountOfPoints; j = i++)
    {
        Point2D a {coordinates.at(i)};
        Point2D b {coordinates.at(j)};

        double A {getDistance(a.getX(), a.getY(), b.getX(), b.getY())};
        double B {getDistance(x, y, a.getX(), a.getY())};
        double C {getDistance(x, y, b.getX(), b.getY())};

        degree += acos((B * B + C * C - A * A) / (2.0 * B * C)) * radian;
    }

    if (abs(static_cast<int>(round(degree)) - 360) <= 0)
            return true;

    return false;
}

bool checkIfSegmentDoesnotRelate (const pos &x, const pos &y, const int &Xmin, const int &Xmax, const int &Ymin, const int &Ymax)
{
    if (x < Xmin || x > Xmax || y < Ymin || y > Ymax)
        return false;

    return true;
}

void describeStatus (const Smart_ptr<Polygon> &polygon, const std::vector<Segment> &arrayOfSegments)
{
    std::vector<Point2D> coordinates {polygon->getCoordinates()};
    int Xmin {0}, Xmax {0}, Ymin {0}, Ymax {0};

    // Определяю минимальные и максимальные позиции
    for (int i = 0; i < static_cast<int>(coordinates.size()) - 1; ++i)
    {
        if (i % 2 != 0)
        {
            Xmax = std::max(coordinates.at(i).getX(), Xmax);
            Xmin = std::min(coordinates.at(i).getY(), Xmin);
        } else
        {
            Ymax = std::max(coordinates.at(i).getX(), Ymax);
            Ymin = std::min(coordinates.at(i).getY(), Ymin);
        }
    }

    int line {1};
    for(Segment segment : arrayOfSegments)
    {
        pos x1 {segment.getX1()};
        pos y1 {segment.getY1()};
        pos x2 {segment.getX2()};
        pos y2 {segment.getY2()};

        // Oтрезок не имеет ничего общего с многоугольником
        if (checkIfSegmentDoesnotRelate(x1, y1, Xmin, Xmax, Ymin, Ymax) && checkIfSegmentDoesnotRelate(x2, y2, Xmin, Xmax, Ymin, Ymax))
        {
            writeResults(3, line);
            ++line;
            continue;
        }

        bool isInside_1 = defineRelation(x1,y1,coordinates);
        bool isInside_2 = defineRelation(x2,y2,coordinates);

        // Oтрезок находится внутри многоугольника
        if (isInside_1 && isInside_2)
            writeResults(0, line);
        // Oтрезок пересекает многоугольник
        if (!isInside_1 && !isInside_2)
            writeResults(1, line);
        // Oтрезок частично пересекает многоугольник
        if (isInside_1 != isInside_2)
            writeResults(2, line);

        ++line;
    }
}

Smart_ptr<Polygon> generatePolygon()
{
    Smart_ptr<Polygon> polygon {new Polygon};
    return polygon;
}

int main (int argc, char *argv[])
{
    if (argc < 3) {return 1;}

    Smart_ptr<Polygon> polygon {generatePolygon()};
    processPolys(argv[1], polygon);

    std::vector<Segment> arrayOfSegments {};
    processLines(argv[2], arrayOfSegments);

    describeStatus(polygon, arrayOfSegments);

    return 0;
}
