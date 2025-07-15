/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <limits>
#include <random>

namespace raytracer {

    void Scene::render(Image &image) const
    {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        for (int y = 0; y < imageHeight; ++y) {
            for (int x = 0; x < imageWidth; ++x) {
                double u = (static_cast<double>(x) + dis(gen)) / imageWidth;
                double v = (static_cast<double>(y) + dis(gen)) / imageHeight;
                Ray r = camera.ray(u, v);
                image.setPixel(x, y, traceRay(r));
            }
        }
    }

    Color Scene::traceRay(const Ray &ray) const
    {
        double closestHit = std::numeric_limits<double>::max();
        const IPrimitive* hitObject = nullptr;

        for (const auto &primitive : primitives) {
            double hitDistance = primitive->hits(ray);
            if (hitDistance > 1e-6 && hitDistance < closestHit) {
                closestHit = hitDistance;
                hitObject = primitive.get();
            }
        }
        if (hitObject) {
            math::Point3D intersectionPoint = ray._origin + (ray._direction * closestHit);
            math::Vector3D normal = hitObject->getNormal(intersectionPoint);
            return calculateLighting(*hitObject, intersectionPoint, normal);
        }
        return Color(0, 0, 0);
    }

    Color Scene::calculateLighting(const IPrimitive &primitive, const math::Point3D &point,
        const math::Vector3D &normal) const
    {
        Color finalColor = primitive.getColor() * ambientLight;
        for (const auto &light : lights) {
            finalColor += primitive.getColor() * light->calculateContribution(point, normal, primitives);
        }
        finalColor.clamp();
        return finalColor;
    }
}