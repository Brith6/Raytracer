/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** case_error
*/

#ifndef ERROR_HANDLER_HPP
    #define ERROR_HANDLER_HPP

#include <string>

namespace raytracer {
    class ErrorHandler {
    public:
        void report(const std::string& message) const;
    };
}

#endif

