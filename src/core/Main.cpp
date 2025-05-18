/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Main.cpp
*/

#include <string>
#include "Raytracer.hpp"

using std::cerr;

int main(int ac, char **av)
{
    core::RayTracer rayTracer(ac, av);

    try {
        return rayTracer.run();
    } catch (const raytracer::Error &e) {
        cerr << e.what() << '\n';
        return 84;
    }
}