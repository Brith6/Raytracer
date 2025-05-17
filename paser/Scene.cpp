/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** scene.cpp
*/

#include "Scene.hpp"

namespace raytracer {
    void Scene::addPrimitive(std::unique_ptr<IPrimitives> primitive)
    {
        primitives_.push_back(std::move(primitive));
    }

    void Scene::addLight(std::unique_ptr<ILigths> light)
    {
        lights_.push_back(std::move(light));
    }

    void Scene::setCamera(const Camera& camera)
    {
        camera_ = camera;
    }
}
