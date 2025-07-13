/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Factory.hpp
*/

#pragma once

#include "../../lights/ILight.hpp"
#include "../../lights/directionalLight/DirectionalLight.hpp"
#include "../../lights/pointLight/PointLight.hpp"
#include "../../primitives/IPrimitive.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include <functional>
#include <memory>
#include <unordered_map>

namespace raytracer
{

class Factory
{
public:
    enum class PrimitiveType { PLANE, SPHERE, CYLINDER, CONE };
    enum class LightType { DIRECTIONAL, POINT };
    
    Factory()
    {
        registerPrimitives();
        registerLights();
    }
    
    ~Factory() = default;
    
    // Créer une primitive
    std::unique_ptr<IPrimitive> createPrimitive(PrimitiveType type);
    
    // Créer une lumière
    std::unique_ptr<ILight> createLight(LightType type);
    
    // Méthodes de création spécifiques pour les primitives
    std::unique_ptr<Plane> createPlane(const std::string &axis, double position, Color &color);
    std::unique_ptr<Sphere> createSphere(const math::Point3D &center, double radius, Color &color);
    
    // Méthodes de création spécifiques pour les lumières
    std::unique_ptr<DirectionalLight> createDirectionalLight(const math::Vector3D &direction, Color &color);
    std::unique_ptr<PointLight> createPointLight(const math::Point3D &origin, Color &color);

private:
    void registerPrimitives();
    void registerLights();
    
    using PrimitiveCreator = std::function<std::unique_ptr<IPrimitive>()>;
    using LightCreator = std::function<std::unique_ptr<ILight>()>;
    
    std::unordered_map<PrimitiveType, PrimitiveCreator> _primitiveCreators;
    std::unordered_map<LightType, LightCreator> _lightCreators;
};

} // namespace raytracer 