/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Error.hpp
*/

#pragma once
#include <exception>
#include <string>

namespace raytracer
{
    class Error : public std::exception {
        public:
            explicit Error(const std::string &message) : _message(message) {}
            ~Error() noexcept override = default;

            const char *what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message;
    };
}