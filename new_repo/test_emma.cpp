/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Test pour les implémentations d'Emmanuela
*/

#include "core/helpers/Color.hpp"
#include "core/helpers/Ray.hpp"
#include "core/math/Math.hpp"
#include "lights/directionalLight/DirectionalLight.hpp"
#include "primitives/plane/Plane.hpp"
#include "core/designPatterns/Factory.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace raytracer;

int main()
{
    std::cout << "=== Test des implémentations d'Emmanuela ===" << std::endl;
    
    // Test de la Factory
    std::cout << "\n1. Test de la Factory:" << std::endl;
    Factory factory;
    
    // Test création d'un plan
    auto plane = factory.createPlane("Z", 0.0, Color(0.5, 0.5, 1.0));
    if (plane) {
        std::cout << "✓ Plan créé avec succès" << std::endl;
    }
    
    // Test création d'une lumière directionnelle
    auto light = factory.createDirectionalLight(
        math::Vector3D(0.0, -1.0, 0.0), 
        Color(1.0, 1.0, 1.0)
    );
    if (light) {
        std::cout << "✓ Lumière directionnelle créée avec succès" << std::endl;
    }
    
    // Test de la classe Plane
    std::cout << "\n2. Test de la classe Plane:" << std::endl;
    Plane planeTest("Z", 0.0, Color(0.5, 0.5, 1.0));
    
    // Test d'intersection avec un rayon
    Ray ray(math::Point3D(0.0, 0.0, 10.0), math::Vector3D(0.0, 0.0, -1.0));
    double distance = planeTest.hits(ray);
    std::cout << "Distance d'intersection: " << distance << std::endl;
    
    // Test de la normale
    math::Vector3D normal = planeTest.getNormal(math::Point3D(0.0, 0.0, 0.0));
    std::cout << "Normale du plan: (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << std::endl;
    
    // Test de la couleur
    Color planeColor = planeTest.getColor();
    std::cout << "Couleur du plan: (" << planeColor.getR() << ", " << planeColor.getG() << ", " << planeColor.getB() << ")" << std::endl;
    
    // Test de la classe DirectionalLight
    std::cout << "\n3. Test de la classe DirectionalLight:" << std::endl;
    DirectionalLight lightTest(math::Vector3D(0.0, -1.0, 0.0), Color(1.0, 1.0, 1.0));
    
    // Test de calcul de contribution lumineuse
    math::Point3D intersectionPoint(0.0, 0.0, 0.0);
    math::Vector3D normal2(0.0, 0.0, 1.0);
    std::vector<std::unique_ptr<IPrimitive>> primitives;
    
    Color contribution = lightTest.calculateContribution(intersectionPoint, normal2, primitives);
    std::cout << "Contribution lumineuse: (" << contribution.getR() << ", " << contribution.getG() << ", " << contribution.getB() << ")" << std::endl;
    
    std::cout << "\n=== Tests terminés ===" << std::endl;
    return 0;
} 