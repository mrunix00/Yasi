#pragma once

#include <cstdint>
#include <string>

namespace Bytecode {
    class Literal {
    public:
        enum Type {
            None,
            Number,
            Boolean,
            String,
        };
        Type type = None;
        virtual ~Literal() = default;
        [[nodiscard]] virtual Literal *copy() const = 0;
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual bool operator==(const Literal &l) const = 0;
    };
}// namespace Bytecode
