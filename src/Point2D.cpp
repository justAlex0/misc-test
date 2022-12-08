#include "constants.hpp"
#include "Point2D.hpp"

Point2D& Point2D::setX (pos x)
{
    m_x = x;
    return *this;
}
Point2D& Point2D::setY (pos y)
{
    m_y = y;
    return *this;
}
