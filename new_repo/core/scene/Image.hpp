/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.hpp
*/

#pragma once

#include "../helpers/Color.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace raytracer {
    class Image {
    public:
        Image(unsigned int width, unsigned int height);
        ~Image() = default;
        void setPixel(unsigned int x, unsigned int y, const Color &color);
        void writeToPPM(const std::string &filepath) const;
        sf::Sprite getSprite();

    private:
        unsigned int _width;
        unsigned int _height;
        std::vector<Color> _pixels;
        sf::Texture _texture;
        sf::Sprite _sprite;
    };
}