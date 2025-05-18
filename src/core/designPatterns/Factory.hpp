/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Factory.hpp
*/

#pragma once
#include "../../primitives/IPrimitives.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../ligths/ILigths.hpp"
#include "../../ligths/pointLigth/PointLigth.hpp"
#include "../../ligths/directionalLigth/DirectionalLigth.hpp"
#include "../../ligths/ambientLigth/ambientLigth.hpp"

#include <memory>
#include <unordered_map>
#include <functional>
using namespace std;


namespace raytracer {
    class Factory {
        public:
            enum PrimitiveType { SPHERE, PLANE, CYLINDER, CONE };
            enum LightType { POINT, DIRECTIONAL, AMBIENT };
            Factory();
            ~Factory() = default;

            template <typename Type>
            void registerPrimitive(const PrimitiveType type)
            {
            _primitives[type] = [this]() {
                    return make_unique<Type>();
                };
            }

            template <typename Type>
            void registerLight(const LightType type)
            {
                _lights[type] = [this]() {
                    return make_unique<Type>();
                };
            }

            unique_ptr<IPrimitives> createPrimitive(PrimitiveType type);
            unique_ptr<ILigths> createLight(LightType type);
        private:
            using PtrPrimitiveCreate = function<unique_ptr<IPrimitives>()>;
            unordered_map<PrimitiveType, PtrPrimitiveCreate> _primitives;

            using PtrLightCreate = function<unique_ptr<ILigths>()>;
            unordered_map<LightType, PtrLightCreate> _lights;
    };
}