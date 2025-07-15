/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.cpp
*/

#include "Image.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace raytracer {

    Image::Image(const unsigned int width, const unsigned int height)
        : _width(width), _height(height), _pixels(width * height) {
        _texture.create(_width, _height);
        _sprite.setTexture(_texture);
    }

    void Image::setPixel(unsigned int x, unsigned int y, const Color &color) {
        if (x < _width && y < _height) {
            _pixels[y * _width + x] = color;
        }
    }

    void Image::writeToPPM(const std::string &filepath) const {
        const std::filesystem::path p(filepath);
        if (!std::filesystem::exists(p.parent_path())) {
            try {
                std::filesystem::create_directories(p.parent_path());
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error creating directory: " << e.what() << '\n';
                return;
            }
        }
        std::ofstream file(filepath, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filepath << "\n";
            return;
        }
        file << "P3\n" << _width << " " << _height << "\n255\n";
        for (const auto& color : _pixels) {
            file << color;
        }
        file.close();
    }

    sf::Sprite Image::getSprite() {
        sf::Image sfImage;
        sfImage.create(_width, _height);

        for (unsigned int y = 0; y < _height; ++y) {
            for (unsigned int x = 0; x < _width; ++x) {
                const auto& color = _pixels[y * _width + x];
                sfImage.setPixel(x, y, sf::Color(
                    static_cast<sf::Uint8>(color.getR() * 255.999),
                    static_cast<sf::Uint8>(color.getG() * 255.999),
                    static_cast<sf::Uint8>(color.getB() * 255.999)
                ));
            }
        }
        _texture.loadFromImage(sfImage); 
        return _sprite;
    }
}