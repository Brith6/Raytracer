/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** ambientLigth.cpp
*/

#include "ambientLigth.hpp"

raytracer::Color raytracer::AmbientLight::directLight(World &world, HitData &data, Color &color 
    , const vector<std::unique_ptr<IPrimitives>> &primitives)
{
    color = _bcolor * _ambient;
    return color;
}