#pragma once

#include <exception>
#include <string>
#include <utility>

class SyntaxError final : public std::exception {
public:
    int line = 0;
    int column = 0;
    std::string message;

    explicit SyntaxError(std::string message) : message(std::move(message)) {}
    SyntaxError(std::string message, const int line, const int column)
        : line(line), column(column), message(std::move(message)) {}
};
