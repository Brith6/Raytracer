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
#include "Camera.hpp"
#include <vector>
#include <memory>

namespace raytracer {
    class Scene {
    private:
    std::vector<std::unique_ptr<Plane>> planes;
    std::vector<std::unique_ptr<Sphere>> spheres;
    std::vector<std::unique_ptr<ILigths>> lights_;
    Camera camera_;
    std::vector<std::unique_ptr<IPrimitives>> primitives_;

public:
    void addPrimitive(std::unique_ptr<IPrimitives> primitive) {
        primitives_.push_back(std::move(primitive));
    }
    void addPlane(std::unique_ptr<Plane> plane) {
        planes.push_back(std::move(plane));
    }
    void addSphere(std::unique_ptr<Sphere> sphere) { 
        spheres.push_back(std::move(sphere));
    }
    void addLight(std::unique_ptr<ILigths> light) {
        lights_.push_back(std::move(light));
    }
    void setCamera(const Camera& camera) {
        camera_ = camera;
    }

    const std::vector<std::unique_ptr<IPrimitives>>& getPrimitives() const { return primitives_; }
    const std::vector<std::unique_ptr<ILigths>>& getLights() const { return lights_; }
    const Camera& getCamera() const { return camera_; }
    const std::vector<std::unique_ptr<Plane>>& getPlanes() const { return planes; }
    const std::vector<std::unique_ptr<Sphere>>& getSpheres() const { return spheres; }
    };
}

#endif
