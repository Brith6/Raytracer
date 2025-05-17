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
        std::vector<std::unique_ptr<IPrimitives>> primitives_;
        std::vector<std::unique_ptr<ILigths>> lights_;
        Camera camera_;
    
    public:
        void addPrimitive(std::unique_ptr<IPrimitives> primitive);
        void addLight(std::unique_ptr<ILigths> light);
        void setCamera(const Camera& camera);

        const std::vector<std::unique_ptr<IPrimitives>>& getPrimitives() const { return primitives_; }
        const std::vector<std::unique_ptr<ILigths>>& getLights() const { return lights_; }
        const Camera& getCamera() const { return camera_; }
    };
}

#endif
