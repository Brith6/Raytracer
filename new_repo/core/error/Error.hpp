/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Error.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace raytracer
{
    class MatrixError : public std::exception 
    {
    public:
        explicit MatrixError(const std::string &message) : _message(message) {}
        
        const char* what() const noexcept override {
            return _message.c_str();
        }
        
    private:
        std::string _message;
    };
} 