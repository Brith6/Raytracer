/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** error
*/

#ifndef CASE_ERROR_HPP
    #define CASE_ERROR_HPP

#include <stdexcept>
#include <string>

class caseError : public std::exception {
private:
    std::string message_;

public:
    explicit caseError(const std::string& message);
    const char* what() const noexcept override;
    void report() const;

};

#endif
