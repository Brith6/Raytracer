/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** DirectionalLight.cpp
*/

#include "DirectionalLight.hpp"
#include "../../core/helpers/Ray.hpp"
#include <algorithm>
#include <limits>

namespace raytracer
{

Color DirectionalLight::calculateContribution(
    const math::Point3D &intersectionPoint,
    const math::Vector3D &normal,
    const std::vector<std::unique_ptr<IPrimitive>>& primitives
) const {
    // Calculer la direction de la lumière vers le point d'intersection
    // Pour une lumière directionnelle, la direction est constante
    math::Vector3D lightDirection = -_direction; // Direction vers la lumière
    
    // Calculer le produit scalaire entre la normale et la direction de la lumière
    double dotProduct = normal.dot(lightDirection);
    
    // Si le produit scalaire est négatif, la face est à l'ombre
    if (dotProduct <= 0.0) {
        return Color(0.0, 0.0, 0.0); // Pas de lumière
    }
    
    // Vérifier les ombres portées
    Ray shadowRay(intersectionPoint, lightDirection);
    double shadowDistance = checkShadow(shadowRay, primitives);
    
    // Si un objet bloque la lumière, pas de contribution
    if (shadowDistance > 0.0 && shadowDistance < std::numeric_limits<double>::max()) {
        return Color(0.0, 0.0, 0.0); // Ombre portée
    }
    
    // Calculer l'intensité lumineuse
    double intensity = dotProduct;
    
    // Retourner la couleur contribuée
    return _color * intensity;
}

double DirectionalLight::checkShadow
(
    const Ray &shadowRay,
    const std::vector<std::unique_ptr<IPrimitive>>& primitives
) const {
    double closestDistance = std::numeric_limits<double>::max();
    
    for (const auto &primitive : primitives) {
        double distance = primitive->hits(shadowRay);
        if (distance > 0.0 && distance < closestDistance) {
            closestDistance = distance;
        }
    }
    
    return closestDistance;
}

} // namespace raytracer 