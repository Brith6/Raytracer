/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
using std::cout;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;

void core::RayTracer::help() const
{
    cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    cout << "\tSCENE_FILE: scene configuration\n";
    exit(0);
}

int core::RayTracer::run() const
{
    string scenef, bfile, output, arg;
    ifstream file;
    raytracer::Scene scene;

    if (_ac < 2)
        help();
    arg = _av[1];
    if (arg == "-h") help();
    else scenef = arg;

    if (scenef.empty())
        throw raytracer::ArgumentError("Error: no scene file provided");
    file.open(scenef);
    if (!file.is_open())
        throw raytracer::ParseError("Error: can't open file " + scenef);
    
    core::Parser parser(scene._camera);
    try {
        parser.parseFile(scenef);
    } catch (const raytracer::ParseError &e) {
        cerr << e.what() << "\n";
        return 84;
    }
    if (!parser.hasBasicElementInFiles())
        return 84;
    raytracer::Image image(
        static_cast<unsigned int>(scene._camera.width),
        static_cast<unsigned int>(scene._camera.height)
    );
    scene.init(parser);
    scene.render(image);
    const std::filesystem::path p(scenef);
    bfile = p.stem().string();
    output = "screenshots/" + bfile + ".ppm";
    image.displayPPM(output);
    return 0;
}