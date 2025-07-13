/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Main.cpp
*/

#include "RayTracer.hpp"
#include "error/Error.hpp"

using std::cerr;

int main(int argc, char **argv)
{
    core::RayTracer rayTracer(argc, argv);

    try {
        return rayTracer.run();
    } catch (const raytracer::ArgumentError &e) {
        cerr << e.what() << '\n';
        return 84;
    } catch (const raytracer::ParseError &e) {
        cerr << e.what() << '\n';
        return 84;
    }
}
