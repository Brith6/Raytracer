/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.cpp
*/

#include "Image.hpp"
#include "../Error.hpp"

#include "Image.hpp"
#include <fstream>
#include <filesystem>
// #include "SceneParser.hpp"
#include "Scene.hpp"

using std::cerr;
using std::ios;
using std::make_pair;
using std::ofstream;
using std::string;
using std::move;
using std::unique_ptr;
using std::make_unique;

unique_ptr<sf::RenderWindow> raytracer::Image::initializeWindow(
    const unsigned int width, const unsigned int height, const bool useSFML
) {
    auto window = make_unique<sf::RenderWindow>();
    if (useSFML) {
        window->create(sf::VideoMode(width, height), "Raytracer");
        window->clear(sf::Color::Black);
        window->display();
    }
    return window;
}

void raytracer::Image::setPixel(const unsigned int x, const unsigned int y,
    const Color &color)
{
    _pixels[tuple<unsigned int, unsigned int>{y, x}] = color;
}

void raytracer::Image::displayPPM(const string &filepath)
{
    const std::filesystem::path p(filepath);

    if (!std::filesystem::exists(p.parent_path())) {
        std::filesystem::create_directories(p.parent_path());
    }
    ofstream file(filepath, ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filepath << "\n";
        return;
    }
    file << "P3\n" << _width << " " << _height << "\n255\n";
    for (unsigned int y = 0; y < _height; y++) {
        for (unsigned int x = 0; x < _width; x++) {
            file << _pixels[tuple<int, int>{y, x}];
        }
    }
    file.close();
}

// void raytracer::Image::display(
//     const string &sceneFile, const string &filepath, const bool isFastRenderer
//     )
// {
//     sf::Image image;
//     image.create(_width, _height);
//     sf::Texture texture;
//     sf::Sprite sprite;
//     Color color;
//     sf::Uint8 red = 0;
//     sf::Uint8 green = 0;
//     sf::Uint8 blue = 0;
//     InputManager managerInput;
//     auto inputObserver = std::make_unique<InputObserver>();

//     inputObserver->bindKeyAction(
//         sf::Keyboard::Key::R,
//         [this, sceneFile, isFastRenderer](const string &filePathLambda) {
//             refreshPicture(sceneFile, filePathLambda, isFastRenderer);
//         }
//     );
//     inputObserver->bindKeyAction(
//         sf::Keyboard::Key::Space,
//         [this](const string &filePathLambda) {
//             displayPPM(filePathLambda);
//         }
//     );

//     managerInput.addObserver(move(inputObserver));
//     for (unsigned int y = 0; y < _height; y++) {
//         for (unsigned int x = 0; x < _width; x++) {
//             color = _pixels[make_pair(y, x)];
//             red = static_cast<sf::Uint8>(color.getR() * 255);
//             green = static_cast<sf::Uint8>(color.getG() * 255);
//             blue = static_cast<sf::Uint8>(color.getB() * 255);
//             image.setPixel(
//                 x, y,
//                 sf::Color(red, green, blue)
//             );
//         }
//         texture.loadFromImage(image);
//         sprite.setTexture(texture);
//         _window.get()->clear();
//         _window.get()->draw(sprite);
//         _window.get()->display();
//     }

//     while (_window.get()->isOpen()) {
//         sf::Event event;
//         while (_window.get()->pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 _window.get()->close();
//             }
//             if (event.type == sf::Event::KeyPressed) {
//                 managerInput.actionKeyPressed(event.key.code, filepath);
//             }
//         }
//     }
// }

unsigned int raytracer::Image::getWidth() const
{
    return _width;
}

unsigned int raytracer::Image::getHeight() const
{
    return _height;
}

// void raytracer::Image::refreshPicture(
//     const string &sceneFile, const string &filepath, const bool isFastRenderer
//     )
// {
//     raytracer::Scene scene;
//     core::SceneParser parser(scene.mCamera);
//     try {
//         parser.parseFile(sceneFile);
//     } catch (const Error &e) {
//         cerr << e.what() << "\n";
//         return;
//     }
//     if (!parser.hasBasicElementInFiles()) {
//         return;
//     }
//     scene.setFastRender(isFastRenderer);
//     scene.init(parser);
//     scene.render(*this);
//     display(sceneFile, filepath, isFastRenderer);
// }