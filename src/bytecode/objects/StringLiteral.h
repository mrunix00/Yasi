#pragma once

#include "Literal.h"
#include <utility>

namespace Bytecode {
    class StringLiteral : public Literal {
        std::string value;

    public:
        explicit StringLiteral(const std::string &str) {
            type = Type::String;
            if (str.front() == '"' && str.back() == '"')
                value = str.substr(1, str.size() - 2);
            else
                value = str;
        }

        [[nodiscard]] std::string asString() const { return value; }

        [[nodiscard]] Literal *copy() const override {
            return new StringLiteral(value);
        }

        [[nodiscard]] std::string toString() const override {
            return value;
        }

        bool operator==(const Literal &l) const override {
            return type == Type::String &&
                   ((StringLiteral *) &l)->value == value;
        }
    };
}// namespace Bytecode