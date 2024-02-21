#pragma once

#include "Literal.h"
#include <cstdint>

namespace Bytecode {
    class NumberLiteral : public Literal {
        int64_t number;

    public:
        explicit NumberLiteral(int64_t number) : number(number) {
            type = Type::Number;
        }

        [[nodiscard]] int64_t asNumber() const { return number; }

        [[nodiscard]] Literal *copy() const override {
            return new NumberLiteral(number);
        }

        [[nodiscard]] std::string toString() const override {
            return "d" + std::to_string(number);
        }

        bool operator==(const Literal &l) const override {
            return type == Type::Number &&
                   ((NumberLiteral *) &l)->number == number;
        }
    };
}// namespace Bytecode