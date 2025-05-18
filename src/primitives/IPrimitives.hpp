/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** IPrimitives.hpp
*/

#pragma once
#include <string>
#include <map>
#include "../core/Ray.hpp"
#include "../core/HitData.hpp"
#include "../core/Range.hpp"
#include "../core/Matrix.hpp"
#include "../core/Color.hpp"

namespace raytracer {
    class IPrimitives {
        public:
            IPrimitives() = default;
            virtual ~IPrimitives() = default;
            virtual bool hits(const Ray& ray, HitData& hitData) const = 0;
            virtual math::Vector3D getNormal(const math::Point3D &point) const = 0;

            Color _bcolor;
            math::Point3D _bcenter;
            int _bradius;
            std::string _baxis;
            int _bposition;
            int _bheight;
            std::map<std::string, math::Matrix<double>> _ballMatrix;
            math::Vector3D _brotation;
    };
}