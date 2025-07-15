/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
#include "../parser/Parser.hpp"
#include "scene/Scene.hpp"
#include "scene/Image.hpp"
#include "error/Error.hpp"
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>

void core::RayTracer::help() const
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE> [-g]\n";
    std::cout << "\tSCENE_FILE: scene configuration file\n";
    std::cout << "\t-g: (optional) display the output in an SFML GUI window\n";
    exit(0);
}

int core::RayTracer::run()
{
    std::string sceneFile;
    bool useSFML = false;

    if (_ac < 2) help();
    for (int i = 1; i < _ac; ++i) {
        std::string arg = _av[i];
        if (arg == "-h" || arg == "--help") help();
        else if (arg == "-g") useSFML = true;
        else sceneFile = arg;
    }
    if (sceneFile.empty()) {
        throw raytracer::ArgumentError("Error: No scene file provided.");
    }

    std::cout << "Parsing scene file: " << sceneFile << std::endl;
    raytracer::Scene scene = core::Parser::parseFile(sceneFile);

    raytracer::Image image(scene.imageWidth, scene.imageHeight);

    std::cout << "Rendering scene (" << scene.imageWidth << "x" << scene.imageHeight << ")..." << std::endl;
    scene.render(image);
    std::cout << "Rendering complete." << std::endl;

    if (useSFML) {
        std::cout << "Displaying in SFML window. Press ESC or close window to exit." << std::endl;
        sf::RenderWindow window(sf::VideoMode(scene.imageWidth, scene.imageHeight), "Raytracer");
        window.setFramerateLimit(60);
        sf::Sprite finalSprite = image.getSprite();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || 
                   (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                {
                    window.close();
                }
            }
            window.clear();
            window.draw(finalSprite);
            window.display();
        }
    } else {
        const std::string bfile = std::filesystem::path(sceneFile).stem().string();
        const std::string outputFile = "screenshots/" + bfile + ".ppm";
        std::cout << "Writing output to " << outputFile << std::endl;
        image.writeToPPM(outputFile);
    }
    return 0;
}