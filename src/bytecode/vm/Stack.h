#pragma once

#include "bytecode/objects/StackObject.h"
#include <cstdint>
#include <cstdlib>

namespace Bytecode {
    class Stack {
        uint8_t *stackData;
        uint8_t *stackTop;
        size_t capacity;
        size_t used;

    public:
        Stack() {
            capacity = 1024;
            stackData = (uint8_t *) malloc(capacity);
            stackTop = stackData;
            used = 0;
        }

        void push(ObjectType, uint8_t *data, size_t amount);
        void push(const StackObject &);
        void push(double data);
        void push(bool data);
        void push(const std::string &data);

        StackObject pop();
        StackObject top();

        void clear();
    };
}