#pragma once

#include "StackObject.h"
#include <cstdint>
#include <limits>
#include <sstream>

namespace Bytecode {
    class NumberLiteral : public StackObject {
        double number;

    public:
        explicit NumberLiteral(double number) : number(number) {
            type = Type::Number;
        }

        [[nodiscard]] double asNumber() const { return number; }

        [[nodiscard]] StackObject *copy() const override {
            return new NumberLiteral(number);
        }

        [[nodiscard]] std::string toString() const override {
            std::stringstream s;
            s << number;
            return s.str();
        }

        bool operator==(const StackObject &l) const override {
            if (type == Type::Number) {
                return std::abs(((NumberLiteral *) &l)->number - number) <
                       (std::numeric_limits<double>::epsilon() * 10);
            }
            return false;
        }
    };
}// namespace Bytecode