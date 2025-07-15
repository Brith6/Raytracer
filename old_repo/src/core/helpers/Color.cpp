/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Color.cpp
*/

#include "Color.hpp"

ostream &operator<<(ostream &os, const raytracer::Color &c)
{
    os << static_cast<int>(c.getR() * 255) << " "
        << static_cast<int>(c.getG() * 255) << " "
        << static_cast<int>(c.getB() * 255) << "\n";
    return os;
}