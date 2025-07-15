/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** case_error
*/

#include "ErrorHandler.hpp"
#include <iostream>

namespace raytracer {
    void ErrorHandler::report(const std::string& message) const
    {
        std::cerr << "Error: " << message << std::endl;
        std::exit(84);
    }
}
