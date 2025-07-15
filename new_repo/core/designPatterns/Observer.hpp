/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Observer.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

namespace raytracer {
    class Observer {
    public:
        Observer(sf::RenderWindow& window) : _window(window) {}
        void update(const sf::Event& event) {
            if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                _window.close();
        }
    private:
        sf::RenderWindow& _window;
    };
}