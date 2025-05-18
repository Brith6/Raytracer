/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Camera.hpp
*/

#pragma once
#include "../core/Ray.hpp"
#include "../core/Rectangle3D.hpp"
#include "../core/Matrix.hpp"
#include <string>
#include <map>

namespace raytracer {
    class Camera {
        public:
            Camera() = default;
            ~Camera() = default;
            Ray ray(const double u, const double v) const;
            math::Point3D ScreenPos(const double u, const double v) const;
            math::Vector3D Direction(const math::Point3D &screenPos) const;

            math::Point3D _origin;
            Rectangle3D _screen;
            int width = 0;
            int height = 0;
            math::Point3D _position = {0, 0, 0};
            double fieldOfView = 0.0;
            std::map<std::string, math::Matrix<double>> _allMatrix;
            math::Vector3D _rotation;
    };
}