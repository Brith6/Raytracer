/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLigth.cpp
*/

#include "PointLigth.hpp"

raytracer::Color raytracer::PointLight::directLight(World &world, HitData &data, Color &color)
{
    math::Vector3D lightDir = _origin - data.p;
    Ray shadowRay(data.p + data.normal * 0.01, lightDir);
    HitData shadowData;
    Color light;

    if (world.hit(shadowRay, shadowData) > 0)
        return Color(0.0, 0.0, 0.0);
    
    float intensity = std::max(0.0, data.normal.dot(lightDir));
    color = _color * _diffuse * intensity;
    return color;
}