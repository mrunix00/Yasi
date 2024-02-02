#ifndef YASI_STACKOBJECT_H
#define YASI_STACKOBJECT_H

#include "Literal.h"

namespace Bytecode {
    class StackObject {
        Literal *literal;

    public:
        ~StackObject() { delete literal; }
        explicit StackObject(Literal *literal) : literal(literal){};

        inline bool operator==(const StackObject& so) {
            return *so.literal == *literal;
        }
    };
}// namespace Bytecode

#endif//YASI_STACKOBJECT_H
