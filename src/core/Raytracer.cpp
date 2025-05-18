/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Raytracer.cpp
*/

#include "Raytracer.hpp"
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
    string sceneFile;
    ifstream file;
    raytracer::Scene scene;
    string baseFilename;
    string outputFilename;
    bool useSFML = false;
    bool isFastRender = false;
    string arg;

    if (_ac < 2) {
        help();
        return 84;
    }
    for (int i = 1; i < _ac; i++) {
        arg = _av[i];
        if (arg == "-h")
            help();
        else if (arg == "-g")
            useSFML = true;
        else if (arg == "-f")
            isFastRender = true;
        else
            sceneFile = arg;
    }
    if (sceneFile.empty())
        throw raytracer::Error("Error: no scene file provided");
    file.open(sceneFile);
    if (!file.is_open())
        throw raytracer::Error("Error: can't open file " + sceneFile);
    
    Parser parser(scene._camera);
    try {
        std::cout << "Rendering scene...\n";
        parser.parseFile(sceneFile);
    } catch (const raytracer::Error &e) {
        cerr << e.what() << "\n";
        return 84;
    }
    if (!parser.hasBasicElementInFiles()) {
        return 84;
    }
    raytracer::Image image(
        static_cast<unsigned int>(scene._camera.width),
        static_cast<unsigned int>(scene._camera.height),
        useSFML
    );
    scene.setFastRender(isFastRender);
    scene.init(parser);
    scene.render(image);
    const std::filesystem::path p(sceneFile);
    baseFilename = p.stem().string();
    outputFilename = "screenshots/" + baseFilename + ".ppm";
    if (useSFML) {
        // image.display(sceneFile, outputFilename, isFastRender);
    } else {
        image.displayPPM(outputFilename);
    }
    return 0;
}