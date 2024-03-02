#pragma once

#include "Literal.h"
#include <cstdint>
#include <limits>
#include <sstream>

namespace Bytecode {
    class NumberLiteral : public Literal {
        double number;

    public:
        explicit NumberLiteral(double number) : number(number) {
            type = Type::Number;
        }

        [[nodiscard]] double asNumber() const { return number; }

        [[nodiscard]] Literal *copy() const override {
            return new NumberLiteral(number);
        }

        [[nodiscard]] std::string toString() const override {
            std::stringstream s;
            s << number;
            return s.str();
        }

        bool operator==(const Literal &l) const override {
            if (type == Type::Number) {
                return std::abs(((NumberLiteral *) &l)->number - number) <
                       (std::numeric_limits<double>::epsilon() * 10);
            }
            return false;
        }
    };
}// namespace Bytecode