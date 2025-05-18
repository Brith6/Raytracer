/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Scene.hpp
*/

#pragma once
#include "../../camera/Camera.hpp"
#include "../Color.hpp"
#include "../designPatterns/Factory.hpp"
#include "../Matrix.hpp"
#include "Image.hpp"
#include "../../parser/Parser.hpp"
#include <iostream>
#include <memory>
#include <random>

using std::unique_ptr;
using std::mt19937;
using std::uniform_real_distribution;

namespace raytracer {
    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void render(Image &image);
            void init(const core::Parser &sceneParser);
            void initPlanes(const vector<Plane> &planes,
                const size_t o, Factory &factory);
            void initSpheres(const vector<Sphere> &spheres,
                const size_t o, Factory &factory);
            // void initCylinders(const vector<Cylinder> &cylinders,
            //     const size_t o, Factory &factory);
            // void initCones(const vector<Cone> &cones,
            //     const size_t o, Factory &factory);
            void initPoints(const vector<PointLight> &points,
                const size_t o, Factory &factory);
            void initDirectionals(const vector<DirectionalLight> &directionals,
                const size_t o, Factory &factory);
            void initAmbients(const vector<AmbientLight> &ambients,
                const size_t o, Factory &factory);
            Color getColor(
                const unsigned int x, const unsigned int y,
                const unsigned int height, const unsigned int width
            );
            Color getLightColor(const IPrimitives &primitive, HitData &data);
            Camera _camera;
            double _ambient = 0.0;
            double _diffuse = 0.0;
            vector<unique_ptr<IPrimitives>> _primitives;
            vector<unique_ptr<ILigths>> _lights;
            mt19937 _gen = mt19937(std::random_device()());
            uniform_real_distribution<double> _dis =
                uniform_real_distribution<double>(0.0, 1.0);
            void setFastRender(const bool isFastRender);
            bool _isFastRender;
    };
}
