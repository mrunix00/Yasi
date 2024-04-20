#pragma once

#include "StackObject.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

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
            if (stackData == nullptr) {
                std::cerr << "Failed to allocate memory for the stack!" << std::endl;
                exit(1);
            }
            stackTop = stackData;
            used = 0;
        }

        void push(ObjectType type, uint8_t *data, size_t amount) {
            if ((used + amount + 1) > capacity) {
                capacity *= 2;
                auto temp = (uint8_t *) realloc(stackData, capacity);
                if (temp == nullptr) {
                    std::cerr << "Failed to allocate memory for the stack!" << std::endl;
                    exit(1);
                }
                stackData = temp;
                stackTop = stackData + used;
            }
            uint8_t *localStackTop = stackTop;
            switch (type) {
                case String:
                    *((char **) localStackTop) = strdup((char *) data);
                    break;
                case Number:
                    *((double *) localStackTop) = *((double *) data);
                    break;
                case Boolean:
                    *localStackTop = *data;
                    break;
                case Lambda:
                    *((size_t *) localStackTop) = *((size_t *) data);
                    break;
                default:
                    break;
            }
            localStackTop += amount;
            *(localStackTop++) = type;
            used += amount + 1;
            stackTop = localStackTop;
        }


        void push(double number) {
            push(ObjectType::Number,
                 (uint8_t *) &number,
                 sizeof(double));
        }

        void push(bool boolean) {
            push(ObjectType::Boolean,
                 (uint8_t *) &boolean,
                 1);
        }

        void push(const std::string &str) {
            push(ObjectType::String,
                 (uint8_t *) str.c_str(),
                 sizeof(char *));
        }

        void push(const size_t lambda) {
            push(ObjectType::Lambda,
                 (uint8_t *) &lambda,
                 sizeof(size_t));
        }

        void push(const StackObject &object) {
            switch (object.type) {
                case ObjectType::Boolean:
                    push(object.asBoolean());
                    break;
                case ObjectType::Number:
                    push(object.asNumber());
                    break;
                case ObjectType::String:
                    push(object.asString());
                    break;
                case ObjectType::Lambda:
                    push(object.asLambda());
                    break;
            }
        }
        StackObject pop() {
            uint8_t type = *(--stackTop);
            switch (type) {
                case ObjectType::Boolean:
                    used = used - 2;
                    stackTop--;
                    return StackObject(*((bool *) stackTop));
                case ObjectType::Number:
                    stackTop -= sizeof(double);
                    used = used - sizeof(double) - 1;
                    return StackObject(*((double *) stackTop));
                case ObjectType::String:
                    stackTop -= sizeof(char *);
                    used = used - sizeof(char *) - 1;
                    return StackObject(std::string(*((char **) stackTop)));
                case ObjectType::Lambda:
                    stackTop -= sizeof(size_t);
                    used = used - sizeof(size_t) - 1;
                    return StackObject(*((size_t *) stackTop));
                default:
                    return StackObject{};
            }
        }

        StackObject top() {
            if (!used)
                return StackObject{};

            uint8_t type = *(stackTop - 1);

            StackObject object{};

            switch (type) {
                case ObjectType::Boolean:;
                    return StackObject(*((bool *) (stackTop - 2)));
                case ObjectType::Number:
                    return StackObject(*((double *) (stackTop - sizeof(double) - 1)));
                case ObjectType::String:
                    return StackObject(std::string(*((char **) (stackTop - sizeof(char *) - 1))));
                default:
                    return object;
            }
        }

        void clear() {
            stackTop = stackData;
            used = 0;
        }
    };
}// namespace Bytecode