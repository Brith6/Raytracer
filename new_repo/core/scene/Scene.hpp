/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Scene.hpp
*/

#pragma once

#include "../../camera/Camera.hpp"
#include "../../primitives/IPrimitive.hpp"
#include "../../lights/ILight.hpp"
#include "Image.hpp"
#include <vector>
#include <memory>

namespace raytracer {
    struct Scene {
        Camera camera;
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        std::vector<std::unique_ptr<ILight>> lights;

        double ambientLight = 0.1;
        double diffuseLight = 1.0;
        int imageWidth = 1920;
        int imageHeight = 1080;

        void render(Image &image) const;

    private:
        Color traceRay(const Ray &ray) const;
        Color calculateLighting(const IPrimitive &primitive, const math::Point3D &point,
            const math::Vector3D &normal) const;
    };
}