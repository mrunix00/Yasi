#pragma once

#include "StackObject.h"
#include <utility>

namespace Bytecode {
    class StringLiteral : public StackObject {
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

        [[nodiscard]] StackObject *copy() const override {
            return new StringLiteral(value);
        }

        [[nodiscard]] std::string toString() const override {
            if (value == "\n") return R"("\n")";
            return '"' + value + '"';
        }

        bool operator==(const StackObject &l) const override {
            return type == Type::String &&
                   ((StringLiteral *) &l)->value == value;
        }
    };
}// namespace Bytecode