/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ambientLigth.cpp
*/

#include "AmbientLigth.hpp"

raytracer::Color raytracer::AmbientLight::directLight(World &world, HitData &data, Color &color)
{
    color = _color * _ambient;
    return color;
}