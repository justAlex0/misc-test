#pragma once

#include <iostream>
#include <vector>

#include "constants.hpp"
#include "Point2D.hpp"

/**
 * @brief Объект отрезка
 */
class Segment
{
    private:
        Point2D m_point1 {0, 0};
        Point2D m_point2 {0, 0};

    public:
        Segment (pos x1, pos y1, pos x2, pos y2)
            : m_point1 {x1, y1}, m_point2 {x2, y2}
        {}
        ~Segment() = default;

        Point2D getPoint1 () const { return m_point1; }
        Point2D getPoint2 () const { return m_point2; }

        pos getX1 () const { return m_point1.getX(); }
        pos getY1 () const { return m_point1.getY(); }
        pos getX2 () const { return m_point2.getX(); }
        pos getY2 () const { return m_point2.getY(); }
};
