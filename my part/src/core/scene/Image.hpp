/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.hpp
*/

#pragma once

#include "../helpers/Color.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <SFML/Graphics.hpp>

using std::map;
using std::tuple;
using std::string;
using std::unique_ptr;

namespace raytracer {
    class Image {
        public:
            Image(const unsigned int width, const unsigned int height,
                const bool useSFML)
                : _width(width), _height(height),
                _window(initializeWindow(width, height, useSFML))  {}
            ~Image() = default;
            unique_ptr<sf::RenderWindow> initializeWindow(
                const unsigned int width, const unsigned int height,
                const bool useSFML);
            void setPixel(const unsigned int x, const unsigned int y,
                const Color &color);
            void displayPPM(const string &filepath);
            void displaySFML();

            unsigned int getWidth() const { return _width; };
            unsigned int getHeight() const { return _height; };
        private:
            unsigned int _width;
            unsigned int _height;
            map<tuple<int, int>, Color> _pixels;
            std::unique_ptr<sf::RenderWindow> _window;
            sf::Texture mTexture;
            sf::Sprite mSprite;
    };
}
