#pragma once

#include <iostream>
#include <vector>

#include "constants.hpp"
#include "Point2D.hpp"

/**
 * @brief Объект многоугольника
 */
class Polygon
{
    private:
        /**
         * @m_coordinates массив из объектов c координатами вершин многоугольника { {x1, y1}, {x2, y2} }
         */
        std::vector<Point2D> m_coordinates {};

    public:
        Polygon() = default;
        ~Polygon() = default;

        /**
         * @brief Заполняет переменную с кординатами прямоугольника
         *
         * @param coordinates
         */
        Polygon& setArrayPos (const std::vector<Point2D> &coordinates);

        /**
         * @brief Возвращает массив с координатами
         *
         */
        std::vector<Point2D> getCoordinates () const { return m_coordinates; }

        /**
         * @brief Выводит в консоль координаты вершин многоугольника
         *
         */
        void print () const;
};
