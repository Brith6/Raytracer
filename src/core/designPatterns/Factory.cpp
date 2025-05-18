/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include "../Error.hpp"

raytracer::Factory::Factory()
{
    registerLight<raytracer::DirectionalLight>(DIRECTIONAL);
    registerLight<raytracer::PointLight>(POINT);
    registerLight<raytracer::AmbientLight>(AMBIENT);
    // registerPrimitive<raytracer::Cone>(CONE);
    // registerPrimitive<raytracer::Cylinder>(CYLINDER);
    registerPrimitive<raytracer::Plane>(PLANE);
    registerPrimitive<raytracer::Sphere>(SPHERE);
}

unique_ptr<raytracer::IPrimitives> raytracer::Factory::createPrimitive(
    const PrimitiveType type)
{
    if (_primitives.find(type) != _primitives.end())
        return _primitives[type]();
    throw Error("Primitive type not found");
}

unique_ptr<raytracer::ILigths> raytracer::Factory::createLight(
    const LightType type)
{
    if (_lights.find(type) != _lights.end())
        return _lights[type]();
    throw Error("Light type not found");
}