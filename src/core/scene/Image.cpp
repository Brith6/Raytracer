/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-raytracer-vanessa.bokove
** File description:
** Image.cpp
*/

#include "Image.hpp"
#include <fstream>
#include <filesystem>
#include "../../parser/Parser.hpp"
#include "Scene.hpp"

using std::cerr;
using std::ios;
using std::make_pair;
using std::ofstream;
using std::string;
using std::move;
using std::unique_ptr;
using std::make_unique;


void raytracer::Image::setPixel(const unsigned int x, const unsigned int y,
    const Color &color)
{
    _pixels[tuple<unsigned int, unsigned int>{y, x}] = color;
}

void raytracer::Image::displayPPM(const string &filepath)
{
    const std::filesystem::path p(filepath);

    if (!std::filesystem::exists(p.parent_path())) {
        std::filesystem::create_directories(p.parent_path());
    }
    ofstream file(filepath, ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filepath << "\n";
        return;
    }
    file << "P3\n" << _width << " " << _height << "\n255\n";
    for (unsigned int y = 0; y < _height; y++) {
        for (unsigned int x = 0; x < _width; x++) {
            file << _pixels[tuple<int, int>{y, x}];
        }
    }
    file.close();
}
