#pragma once

#include "Literal.h"
namespace Bytecode {
    class BooleanLiteral : public Literal {
        bool boolean;

    public:
        explicit BooleanLiteral(bool boolean) : boolean(boolean) {
            type = Type::Boolean;
        }

        [[nodiscard]] bool asBoolean() const { return boolean; }

        [[nodiscard]] Literal *copy() const override {
            return new BooleanLiteral(boolean);
        }

        [[nodiscard]] std::string toString() const override {
            return "#" + (boolean ? std::string("true") : std::string("false"));
        }

        bool operator==(const Literal &l) const override {
            return type == Type::Boolean &&
                   ((BooleanLiteral *) &l)->boolean == boolean;
        }
    };
}// namespace Bytecode