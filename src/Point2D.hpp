#pragma once

#include "constants.hpp"

/**
 * @brief Объект 2D точки
 */
class Point2D
{
    private:
        pos m_x {0};
        pos m_y {0};

    public:
        Point2D(pos x, pos y)
            : m_x {x}, m_y {y}
        {}
        ~Point2D() = default;

        Point2D& setX (pos x);
        Point2D& setY (pos y);

        pos getX () const {return m_x;}
        pos getY () const {return m_y;}
};
