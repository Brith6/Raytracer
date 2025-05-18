/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** directionalLigth.cpp
*/

#include "DirectionalLigth.hpp"

bool raytracer::DirectionalLight::directLight(World &world, HitData &data, Color &color)
{
    math::Vector3D lightDir = -_direction;
    Ray shadowRay(data.p, lightDir);
    HitData shadowData;
    Color light;

    if (world.hit(shadowRay, shadowData) > 0)
        return false;
    
    float intensity = std::max(0.0, data.normal.dot(lightDir));
    color = _color * intensity;
    return true;
}