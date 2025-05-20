/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Error.hpp
*/

#pragma once

#include <stdexcept>
#include <string>

using std::exception;
using std::string;

namespace raytracer {
    class ArgumentError : public exception {
        public:
            explicit ArgumentError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class ParseError : public exception {
        public:
            explicit ParseError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class MatrixError : public exception {
        public:
            explicit MatrixError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };
}
