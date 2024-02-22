#pragma once

#include "Literal.h"
#include <limits>
namespace Bytecode {
    class DecimalNumberLiteral : public Literal {
        float decimal;

    public:
        explicit DecimalNumberLiteral(float decimal) : decimal(decimal) {
            type = Type::DecimalNumber;
        }

        [[nodiscard]] float asDecimalNumber() const { return decimal; }

        [[nodiscard]] Literal *copy() const override {
            return new DecimalNumberLiteral(decimal);
        }

        [[nodiscard]] std::string toString() const override {
            return "f" + std::to_string(decimal);
        }

        bool operator==(const Literal &l) const override {
            return type == Type::DecimalNumber &&
                   ((DecimalNumberLiteral *) &l)->decimal == decimal;
        }
    };
}// namespace Bytecode