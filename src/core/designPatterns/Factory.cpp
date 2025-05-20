/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include "../error/Error.hpp"

using enum raytracer::Factory::LightType;
using enum raytracer::Factory::PrimitiveType;

raytracer::Factory::Factory()
{
    registerLight<raytracer::DirectionalLight>(DIRECTIONAL);
    registerLight<raytracer::PointLight>(POINT);
    registerPrimitive<raytracer::Cone>(CONE);
    registerPrimitive<raytracer::Cylinder>(CYLINDER);
    registerPrimitive<raytracer::Plane>(PLANE);
    registerPrimitive<raytracer::Sphere>(SPHERE);
}

unique_ptr<raytracer::IPrimitive> raytracer::Factory::createPrimitive(
    const PrimitiveType type)
{
    if (mCreatorsPrimitives.contains(type)) {
        return mCreatorsPrimitives[type]();
    }
    throw raytracer::ParseError("Primitive type not found");
}

unique_ptr<raytracer::ILight> raytracer::Factory::createLight(
    const LightType type)
{
    if (mCreatorsLights.contains(type)) {
        return mCreatorsLights[type]();
    }
    throw raytracer::ParseError("Light type not found");
}
