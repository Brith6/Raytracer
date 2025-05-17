/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** scene.hpp
*/

#ifndef SCENE_HPP
    #define SCENE_HPP

#include "primitives/IPrimitives.hpp"
#include "../src/ligths/ILigths.hpp"
#include "../src/primitives/plane/Plane.hpp"
#include "../src/primitives/sphere/Sphere.hpp"
#include "Camera.hpp"
#include <vector>
#include <memory>

namespace raytracer {
    class Scene {
    private:
        std::vector<Plane> planes;
        std::vector<Sphere> spheres;
        std::vector<ILigths> lights_;
        Camera camera_;

    public:
        void addPlane(const Plane& plane) {
            planes.push_back(plane);
        }
        void addSphere(const Sphere& sphere) {
            spheres.push_back(sphere);
        }
        void addLight(const ILigths& light) {
            lights_.push_back(light);
        }
        void setCamera(const Camera& camera) {
            camera_ = camera;
        }

        const std::vector<Plane>& getPlanes() const { return planes; }
        const std::vector<Sphere>& getSpheres() const { return spheres; }
        const std::vector<ILigths>& getLights() const { return lights_; }
        const Camera& getCamera() const { return camera_; }
    };
}

#endif
