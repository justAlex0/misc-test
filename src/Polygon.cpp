#include "constants.hpp"
#include "Polygon.hpp"

Polygon& Polygon::setArrayPos (const std::vector<Point2D> &coordinates)
{
    m_coordinates = coordinates;
    return *this;
}
void Polygon::print() const
{
    for (int i = 0; i < static_cast<int>(m_coordinates.size()); ++i)
    {
        std::cout << "x" << (i + 1) << "=" << m_coordinates.at(i).getX() << std::endl;
        std::cout << "y" << (i + 1) << "=" << m_coordinates.at(i).getY() << std::endl;
    }
}
