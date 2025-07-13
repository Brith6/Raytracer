/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Cylinder.hpp
*/

#pragma once
#include "../IPrimitive.hpp"
#include <map>

namespace raytracer {
    class Cylinder : public IPrimitive {
        public:
            Cylinder() = default;
            Cylinder(const int x, const int y, const int z,
                const int radius, const int height, const Color &color,
                const map<string, math::Matrix<double>> &allMatrix,
                const math::Vector3D &vectorRotation)
                : mX(x), mY(y), mZ(z), mRadius(radius),
                    mHeight(height), mColor(color), mAllMatrix(allMatrix),
                    mVectorRotation(vectorRotation) {}
            ~Cylinder() override = default;

            double hits(const Ray &ray) override;
            math::Vector3D rotateVector(math::Vector3D vectorBase);
            math::Vector3D rotateX(math::Vector3D vectorBase);
            math::Vector3D rotateY(math::Vector3D vectorBase);
            math::Vector3D rotateZ(math::Vector3D vectorBase);
            math::Vector3D getNormal(const math::Point3D &point) const override;

            int mX = 0;
            int mY = 0;
            int mZ = 0;
            int mRadius = 0;
            int mHeight = 0;
            Color mColor;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}
