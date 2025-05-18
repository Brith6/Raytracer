/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** color.h
*/

#pragma once
#include <iostream>
using std::ostream;

namespace raytracer {
    class Color {
        public:
            Color() = default;
            Color(const double r, const double g, const double b) : _r(r), _g(g), _b(b) {}
            ~Color() = default;
            
            Color operator*(const int other) const {
                return Color(_r * other, _g * other, _b * other);
            }
            Color operator*(const double other) const {
                return Color(_r * other, _g * other, _b * other);
            }
            Color operator*(const Color &other) const {
                return raytracer::Color(
                    _r * other._r,
                    _g * other._g,
                    _b * other._b
                );
            }
            Color operator/=(const int other) {
                _r /= other;
                _g /= other;
                _b /= other;
                return *this;
            }
            Color operator+=(const Color &other) {
                _r += other._r;
                _g += other._g;
                _b += other._b;
                return *this;
            }
            Color operator+=(const double other) {
                _r = _r + other;
                _g = _g + other;
                _b = _b + other;
                return *this;
            }
            Color operator+(const double other) const {
                return Color(_r + other, _g + other, _b + other);
            }
            Color operator/(const int other) const {
                return Color(_r / other, _g / other, _b / other);
            }
            void clamp()
            {
                _r = _r < 0.0 ? 0.0 : _r;
                _r = _r > 1.0 ? 1.0 : _r;
                _g = _g < 0.0 ? 0.0 : _g;
                _g = _g > 1.0 ? 1.0 : _g;
                _b = _b < 0.0 ? 0.0 : _b;
                _b = _b > 1.0 ? 1.0 : _b;
            }
            double getR() const { return _r; }
            double getG() const { return _g; }
            double getB() const { return _b; }

        private:
            double _r = 0;
            double _g = 0;
            double _b = 0;
    };
}

ostream &operator<<(ostream &os, const raytracer::Color &c);