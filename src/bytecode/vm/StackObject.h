#ifndef YASI_STACKOBJECT_H
#define YASI_STACKOBJECT_H

#include "Literal.h"

namespace Bytecode {
    class StackObject {

    public:
        ~StackObject() { delete literal; }
        explicit StackObject(Literal *literal) : literal(literal){};

        inline bool operator==(const StackObject& so) {
            return *so.literal == *literal;
        }
        Literal *literal;
    };
}// namespace Bytecode

#endif//YASI_STACKOBJECT_H
