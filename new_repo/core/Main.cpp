/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Main.cpp
*/

#include "RayTracer.hpp"
#include "error/Error.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    core::RayTracer rayTracer(argc, argv);

    try {
        return rayTracer.run();
    } catch (const std::exception &e) {
        std::cerr << "Fatal Error: " << e.what() << '\n';
        return 84;
    }
}
