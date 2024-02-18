#pragma once

#include "Literal.h"

namespace Bytecode {
    class StackObject {
    public:
        Literal *literal;
        ~StackObject() { delete literal; }
        explicit StackObject(Literal *literal) : literal(literal){};

        bool operator==(const StackObject& so) const {
            if (this == nullptr) return false;
            return *so.literal == *literal;
        }
    };
}// namespace Bytecode
