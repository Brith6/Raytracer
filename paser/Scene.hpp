/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** scene.hpp
*/

#ifndef SCENE_HPP
    #define SCENE_HPP

#include "../src/primitives/IPrimitives.hpp"
#include "../src/ligths/ILigths.hpp"
#include "../src/primitives/plane/Plane.hpp"
#include "../src/primitives/sphere/Sphere.hpp"
#include "../src/ligths/pointLigth/PointLigth.hpp"
#include "../src/ligths/directionalLigth/DirectionalLigth.hpp"
#include "../src/ligths/ambientLigth/AmbientLigth.hpp"
#include "../src/camera/Camera.hpp"
#include <vector>
#include <memory>

namespace raytracer {
    class Scene {
    private:
        std::vector<Plane> planes;
        std::vector<Sphere> spheres;
        std::vector<ILigths> lights_;
        std::vector<AmbientLight> _ambientLights;
        std::vector<PointLight> _pointLights;
        std::vector<DirectionalLight>  _directionalLights;
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
        void addAmbientLight(AmbientLight&& l)
        {
             _ambientLights.push_back(std::move(l));
        }
        void addPointLight(PointLight&& l)
        {
             _pointLights.push_back(std::move(l));
        }
        void addDirectionalLight(DirectionalLight&& l)
        { 
            _directionalLights.push_back(std::move(l));
        }

        const std::vector<Plane>& getPlanes() const { return planes; }
        const std::vector<Sphere>& getSpheres() const { return spheres; }
        const std::vector<ILigths>& getLights() const { return lights_; }
        const Camera& getCamera() const { return camera_; }
        const std::vector<AmbientLight>& getAmbientLights() const { return _ambientLights;}
        const std::vector<PointLight>& getPointLights() const { return _pointLights;}
        const std::vector<DirectionalLight>& getDirectionalLights()const { return _directionalLights;}


    };
}

#endif

