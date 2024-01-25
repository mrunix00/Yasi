#ifndef YASI_SYNTAXERROR_H
#define YASI_SYNTAXERROR_H

#include <exception>
#include <string>
#include <utility>

class SyntaxError : public std::exception {
public:
    int line = 0;
    int column = 0;
    std::string message;

    explicit SyntaxError(std::string message) : message(std::move(message)) {}
    SyntaxError(std::string message, int line, int column)
        : message(std::move(message)), line(line), column(column) {}
};

#endif
