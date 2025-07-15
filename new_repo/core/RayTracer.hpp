/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** RayTracer.hpp
*/

#pragma once
#include "designPatterns/Observer.hpp"
#include <iostream>

namespace core {
    class RayTracer {
        public:
            RayTracer(int ac, char **const av)
                : _ac(ac), _av(av) {}
            ~RayTracer() = default;

            void help() const;
            int run();
            void notifyObserver(raytracer::Observer,
                const sf::Event& event);
        private:
            int _ac;
            char **_av;
    };
}