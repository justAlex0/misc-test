#pragma once

#include "constants.hpp"
#include "smart_ptr.hpp"
#include "Point2D.hpp"
#include "Polygon.hpp"
#include "Segment.hpp"

/**
 * @brief Обрабатывает файл с координатами вершин многоугольника
 *
 * @param file Файл
 * @param polygon Класс с объектом полигона
 */
void processPolys(const char *file, Polygon &polygon);

/**
 * @brief Обрабатывает файл с координатами отрезка
 *
 * @param file Файл
 * @param arrayOfSegments Массив с объектами отрезков
 */
void processLines (const char *file, std::vector<Segment> &arrayOfSegments);

/**
 * @brief Выводит результаты в файл
 *
 * @param status ID статуса
 * @param line Номер линии координаты отрезка из файла с координатами отрезка
 */
void writeResults (const int &status, const int &line);

/**
 * @brief Выдает длину между точками
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return Длина
 */
double getDistance (const pos &x1, const pos &y1, const pos &x2, const pos &y2);

/**
 * @brief Определяет, принадлежит ли точка многугольнику
 * Работает методом сложения всех углов многоульника относительно точки
 * если сумма больше 360 град, то точка снаружи
 *
 * @param x Координата X точки
 * @param y Координата Y точки
 * @param coordinates Массив координат вершин многоугольника
 * @return true - если точка внутри многоугольника
 */
bool defineRelation (const pos &x, const pos &y, const std::vector<std::vector<pos>> &coordinates);

/**
 * @brief Определяет, лежит ли точка рядом с прямоугольником
 *
 * @param x Координата X точки
 * @param y Координата Y точки
 * @param Xmin Минимальная координата по оси X у многоугольника
 * @param Xmax Максимальная координата по оси X у многоугольника
 * @param Ymin Минимальная координата по оси Y у многоугольника
 * @param Ymax Максимальная координата по оси Y у многоугольника
 * @return true - если точка не рядом с многоугольником
 */
bool checkIfSegmentDoesnotRelate (const pos &x, const pos &y, const int &Xmin, const int &Xmax, const int &Ymin, const int &Ymax);

/**
 * @brief Определяет отношение отрезков и многоугольника
 *
 * @param polygon Класс с объектом многоульника
 * @param arrayOfSegments Массив с координатами отрезков
 */
void describeStatus (const Polygon &polygon, const std::vector<Segment> &arrayOfSegments);

/**
 * @brief Генерирует динамически объект Полигона
 *
 */
Smart_ptr<Polygon> generatePolygon();
