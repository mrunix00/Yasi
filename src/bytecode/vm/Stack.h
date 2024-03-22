#pragma once

#include "bytecode/objects/StackObject.h"
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
            switch (type) {
                case String:
                    *((char **) stackTop) = strdup((char *) data);
                    break;
                case Number:
                    *((double *) stackTop) = *((double *) data);
                    break;
                case Boolean:
                    *stackTop = *data;
                    break;
                case Lambda:
                    *((size_t *) stackTop) = *((size_t *) data);
                    break;
                default:
                    break;
            }
            stackTop += amount;
            *(stackTop++) = type;
            used += amount + 1;
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
            size_t size;
            switch (type) {
                case ObjectType::Boolean:
                    size = 1;
                    used = used - size - 1;
                    stackTop -= size;
                    return StackObject(*((bool *) stackTop));
                case ObjectType::Number:
                    size = sizeof(double);
                    stackTop -= size;
                    used = used - size - 1;
                    return StackObject(*((double *) stackTop));
                case ObjectType::String:
                    size = sizeof(char *);
                    stackTop -= size;
                    used = used - size - 1;
                    return StackObject(std::string(*((char **) stackTop)));
                case ObjectType::Lambda:
                    size = sizeof(size_t);
                    stackTop -= size;
                    used = used - size - 1;
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
            size_t size;

            switch (type) {
                case ObjectType::Boolean:
                    size = 1;
                    return StackObject(*((bool *) (stackTop - size - 1)));
                case ObjectType::Number:
                    size = sizeof(double);
                    return StackObject(*((double *) (stackTop - size - 1)));
                case ObjectType::String:
                    size = sizeof(char *);
                    return StackObject(std::string(*((char **) (stackTop - size - 1))));
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