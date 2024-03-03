#include "StackObject.h"
#include <cstring>

namespace Bytecode {
    void Stack::push(ObjectType type, uint8_t *data, size_t amount) {
        if ((used + amount + 1) > capacity) {
            capacity *= 2;
            stackData = (uint8_t *) realloc(stackData, capacity);
        }
        if (type == ObjectType::String) {
            char *str = strdup((char *) data);
            memcpy(stackTop, &str, amount);
        } else
            memcpy(stackTop, data, amount);
        stackTop += amount;
        *(stackTop++) = type;
        used += amount + 1;
    }

    void Stack::push(double number) {
        push(ObjectType::Number,
             (uint8_t *) &number,
             sizeof(double));
    }

    void Stack::push(bool boolean) {
        push(ObjectType::Boolean,
             (uint8_t *) &boolean,
             1);
    }

    void Stack::push(const std::string &str) {
        push(ObjectType::String,
             (uint8_t *) str.c_str(),
             sizeof(char *));
    }

    StackObject Stack::pop() {
        uint8_t type = *(--stackTop);
        StackObject object{};
        size_t size;
        switch (type) {
            case ObjectType::Boolean:
                size = 1;
                object = StackObject(*((bool *) (stackTop - size)));
                break;
            case ObjectType::Number:
                size = sizeof(double);
                object = StackObject(*((double *) (stackTop - size)));
                break;
            case ObjectType::String:
                size = sizeof(char *);
                object = StackObject(std::string(*((char **) (stackTop - size))));
                break;
            default:
                size = -1;
        }

        stackTop -= size;
        used = used - size - 1;

        return object;
    }
    StackObject Stack::top() {
        uint8_t type = *(stackTop - 1);

        if (!used)
            return StackObject{};

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

    void Stack::clear() {
        stackTop = stackData;
        used = 0;
    }
}// namespace Bytecode