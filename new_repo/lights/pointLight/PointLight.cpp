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

  Color raytracer::PointLight::calculateContribution(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const std::vector<std::unique_ptr<IPrimitive>>& primitives
            )const {
        math::Vector3D lightDirection = (_origin - intersectionPoint).normalized();
        double cosTheta = normal.dot(lightDirection);
        if (cosTheta <= 0) {
            return Color(0, 0, 0);
        }

        double distance = (_origin - intersectionPoint).length();
        double attenuation = 1.0; // Ou : 1.0 / (distance * distance) pour atténuation réaliste

        Ray shadowRay(intersectionPoint + (normal * 0.01), lightDirection);
        for (const auto& primitive : primitives) {
            double t = primitive->hits(shadowRay);
            if (t > 0 && t < distance) {
                return Color(0, 0, 0);
            }
        }

        return _color * (cosTheta * attenuation);
    }