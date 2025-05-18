/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** directionalLigth.cpp
*/

#include "DirectionalLigth.hpp"

raytracer::Color raytracer::DirectionalLight::directLight(World &world, HitData &data, Color &color 
    , const vector<std::unique_ptr<IPrimitives>> &primitives)
{
    math::Vector3D lightDir = math::Vector3D::normalize(_direction);
    Ray shadowRay(data.p + (data.normal * 0.01), lightDir);
    HitData shadowData;

    const double closestHit = world.hit(shadowRay, primitives);
    if (closestHit < (_origin - data.p).length()) {
        return Color(0.0, 0.0, 0.0);
    }
    const double distance = (_origin - data.p).length();
    const double attenuation = 1.0 / distance;
    
    color = _bcolor * attenuation;
    return color;
}