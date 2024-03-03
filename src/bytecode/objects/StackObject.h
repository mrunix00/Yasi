#pragma once

#include <cstdint>
#include <string>

namespace Bytecode {
    class StackObject {
    public:
        enum Type {
            None,
            Number,
            Boolean,
            String,
        };
        Type type = None;
        virtual ~StackObject() = default;
        [[nodiscard]] virtual StackObject *copy() const = 0;
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual bool operator==(const StackObject &l) const = 0;
    };
}// namespace Bytecode
