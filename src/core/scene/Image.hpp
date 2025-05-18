/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.hpp
*/

#pragma once

#include "../Color.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <memory>


using std::map;
using std::tuple;
using std::string;
using std::unique_ptr;

namespace raytracer {
    class Image {
        public:
            Image(const unsigned int width, const unsigned int height,
                const bool useSFML) : _width(width), _height(height) 
                , _window(initializeWindow(width, height, useSFML)) {}
            
            ~Image() = default;

            unique_ptr<sf::RenderWindow> initializeWindow(
                const unsigned int width, const unsigned int height,
                const bool useSFML);
            void setPixel(const unsigned int x, const unsigned int y,
                const Color &color);
            // void display(const string &sceneFile, const string &filepath,
            //     const bool isFastRenderer);
            void displayPPM(const string &filepath);

            unsigned int getWidth() const;
            unsigned int getHeight() const;
            // void refreshPicture(const string &sceneFile, const string &filepath,
            //     const bool isFastRenderer);
        private:
            unsigned int _width;
            unsigned int _height;
            map<tuple<int, int>, Color> _pixels;
            unique_ptr<sf::RenderWindow> _window;
            sf::Texture _texture;
            sf::Sprite _sprite;
    };
}