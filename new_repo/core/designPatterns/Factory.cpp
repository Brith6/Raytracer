/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Factory.cpp
*/

#include "Factory.hpp"
#include <iostream>

namespace raytracer
{

void Factory::registerPrimitives()
{
    // Enregistrer les créateurs de primitives
    _primitiveCreators[PrimitiveType::PLANE] = []() {
        return std::make_unique<Plane>();
    };
    
    _primitiveCreators[PrimitiveType::SPHERE] = []() {
        return std::make_unique<Sphere>();
    };
    
    // Les autres primitives seront ajoutées quand elles seront implémentées
    // _primitiveCreators[PrimitiveType::CYLINDER] = []() {
    //     return std::make_unique<Cylinder>();
    // };
    // _primitiveCreators[PrimitiveType::CONE] = []() {
    //     return std::make_unique<Cone>();
    // };
}

void Factory::registerLights()
{
    // Enregistrer les créateurs de lumières
    _lightCreators[LightType::DIRECTIONAL] = []() {
        return std::make_unique<DirectionalLight>();
    };
    
    _lightCreators[LightType::POINT] = []() {
        return std::make_unique<PointLight>();
    };
}

std::unique_ptr<IPrimitive> Factory::createPrimitive(PrimitiveType type)
{
    auto it = _primitiveCreators.find(type);
    if (it != _primitiveCreators.end()) {
        return it->second();
    }
    
    std::cerr << "Error: Unknown primitive type" << std::endl;
    return nullptr;
}

std::unique_ptr<ILight> Factory::createLight(LightType type)
{
    auto it = _lightCreators.find(type);
    if (it != _lightCreators.end()) {
        return it->second();
    }
    
    std::cerr << "Error: Unknown light type" << std::endl;
    return nullptr;
}

std::unique_ptr<Plane> Factory::createPlane(const std::string &axis, double position, Color &color)
{
    return std::make_unique<Plane>(axis, position, color);
}

std::unique_ptr<Sphere> Factory::createSphere(const math::Point3D &center, double radius, Color &color)
{
    return std::make_unique<Sphere>(center, radius, color);
}

std::unique_ptr<DirectionalLight> Factory::createDirectionalLight(const math::Vector3D &direction, Color &color)
{
    return std::make_unique<DirectionalLight>(direction, color);
}

std::unique_ptr<PointLight> Factory::createPointLight(const math::Point3D &origin, Color &color)
{
    return std::make_unique<PointLight>(origin, color);
}

}
