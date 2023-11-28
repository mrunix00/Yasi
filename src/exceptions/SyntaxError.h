#ifndef YASI_SYNTAXERROR_H
#define YASI_SYNTAXERROR_H

#include <exception>
#include <string>
#include <utility>

class SyntaxError : public std::exception {
public:
    std::string message;

    explicit SyntaxError(std::string message)
            : message(std::move(message)) {}
};

#endif
