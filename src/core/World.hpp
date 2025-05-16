/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** World.hpp
*/

#pragma once
#include "../primitives/IPrimitives.hpp"
#include "../ligths/ILigths.hpp"
#include "Range.hpp"
#include <list>
#include <memory>

namespace raytracer {

    class World {
        public:
            World() {};
            ~World() {};

            void addObject(std::shared_ptr<IPrimitives> obj) {
                _objects.push_back(obj);
            }
            std::list<std::shared_ptr<IPrimitives>> &objects() {
                return _objects;
            }

            // void addLight(std::shared_ptr<ILigths> light) {
            //     _ligths.push_back(light);
            // }
            // std::list<std::shared_ptr<ILigths>> &lights() {
            //     return _ligths;
            // }

            bool hit(const Ray &r, HitData &data) const {
                HitData tmp;
                bool hit = false;
                float closest = std::numeric_limits<float>::max();
                math::Range range(0.0, closest);
        
                for (auto &obj : _objects) {
                    if (obj->hits(r, tmp) && range.isInRange(tmp.t)
                        && tmp.t < closest) {
                        hit = true;
                        closest = tmp.t;
                        data = tmp;
                    }
                }
                return hit;
            }        
            void clear() {
                _objects.clear();
                // _ligths.clear();
            }

        private:
            std::list<std::shared_ptr<IPrimitives>> _objects;
            // std::list<std::shared_ptr<ILigths>> _ligths;
    };

    // std::ostream &operator<<(std::ostream &os, World &w);
}