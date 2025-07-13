/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>
#include "../helpers/Color.hpp"
#include "../math/Math.hpp"
#include "../IPrimitive.hpp" 

namespace raytracer {

    Color PointLight::calculateContribution(
        const math::Point3D &intersectionPoint,
        const math::Vector3D &normal,
        const std::vector<std::unique_ptr<IPrimitive>> &primitives
    ) const {
        // Calculer la direction de la lumière
        math::Vector3D lightDir = _origin - intersectionPoint;
        math::Vector3D lightDirection = lightDir.normalized();
        double cosTheta = normal.dot(lightDirection);
        if (cosTheta <= 0) {
            return Color(0, 0, 0);
        }

        // Calculer la distance pour l'atténuation
        double distance = lightDir.length();
        double attenuation = 1.0; // Ou : 1.0 / (distance * distance)

        // Vérifier les ombres portées
        Ray shadowRay(intersectionPoint + (normal * 0.01), lightDirection);
        for (const auto& primitive : primitives) {
            double t = primitive->hits(shadowRay);
            if (t > 0 && t < distance) {
                return Color(0, 0, 0);
            }
        }

        // Calculer la contribution diffuse
        double factor = cosTheta * attenuation;
        return _color * factor;

    }
}