/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Parser.hpp
*/

#pragma once

#include "../lights/directionalLight/DirectionalLight.hpp"
#include "../lights/pointLight/PointLight.hpp"
#include "../primitives/cone/Cone.hpp"
#include "../primitives/cylinder/Cylinder.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../camera/Camera.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libconfig.h++>
#include <vector>

using raytracer::Camera;
using raytracer::Cylinder;
using raytracer::DirectionalLight;
using raytracer::Plane;
using raytracer::PointLight;
using raytracer::Sphere;
using raytracer::Cone;
using std::string;
using std::vector;

namespace core {
    class Parser {
        public:
            explicit Parser(Camera &camera) : _camera(camera) {};
            ~Parser() = default;

            void parseCamera(const libconfig::Config &cfg);
            void parsePrimitive(const libconfig::Config &cfg);
            void parseSpheres(const libconfig::Setting &spheresSetting);
            void parsePlanes(const libconfig::Setting &planesSetting);
            void parseCylinders(const libconfig::Setting &cylindersSetting);
            void parseCones(const libconfig::Setting &conesSetting);
            void parseLights(const libconfig::Config &cfg);
            void parseFile(const string &filename);
            bool hasBasicElementInFiles();

            vector<Sphere> getSpheres() const { return _spheres; };
            vector<Cone> getCones() const { return _cones; };
            vector<Plane> getPlanes() const { return _planes; };
            vector<Cylinder> getCylinders() const { return _cylinders; };
            vector<PointLight> getPointLights() const { return _pointLights; };
            vector<DirectionalLight> getDirectionalLights() const { return _directionalLights; };
            double getAmbient() const { return _ambient; };
            double getDiffuse() const { return _diffuse; };

        private:
            void parseRotation(
                const libconfig::Setting &fileconfigRotation,
                map<string, math::Matrix<double>> &allMatrix,
                math::Vector3D &vectorRotation
            );
            void parseTranslation(
                const libconfig::Setting &fileconfigTranslation,
                map<string, math::Matrix<double>> &allMatrix
            );
            void parseScale(
                const libconfig::Setting &fileconfigScale,
                map<string, math::Matrix<double>> &allMatrix
            );

            Camera &_camera;
            double _ambient;
            double _diffuse;
            vector<Cylinder> _cylinders;
            vector<DirectionalLight> _directionalLights;
            vector<Plane> _planes;
            vector<PointLight> _pointLights;
            vector<Sphere> _spheres;
            vector<Cone> _cones;
    };
}
