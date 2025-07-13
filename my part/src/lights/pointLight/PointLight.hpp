/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** PointLight.hpp
*/

#pragma once
#include "../ILight.hpp"
#include <iostream>
#include <map>

using std::string;
using std::map;

namespace raytracer {
    class PointLight : public ILight {
        public:
            PointLight() = default;
            PointLight(const int originX, const int originY, const int originZ,
                const Color &color,
                const map<string, math::Matrix<double>> &allMatrix,
                const math::Vector3D vectorRatation)
                : mOrigin(originX, originY, originZ), mColor(color),
                mAllMatrix(allMatrix), mVectorRotation(vectorRatation) {}
            ~PointLight() override = default;

            Color getColorShadow(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const vector<unique_ptr<IPrimitive>> &primitives
            ) override;

            math::Point3D mOrigin;
            Color mColor;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}