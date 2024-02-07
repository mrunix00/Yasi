#pragma once

namespace Bytecode {
    enum class Boolean {
        True,
        False
    };

    class Literal {
    public:
        enum class Type {
            Integer,
            Boolean
        };
        int int_literal{};
        Boolean bool_literal{};
        Type type;

        explicit Literal(const bool b) : bool_literal(b ? Boolean::True : Boolean::False),
                                         type(Type::Boolean) {}
        explicit Literal(const Boolean b) : bool_literal(b), type(Type::Boolean) {}
        explicit Literal(const int val) : int_literal(val), type(Type::Integer) {}

        bool operator==(const Literal l) const {
            if (type == l.type) {
                if (type == Type::Boolean)
                    return bool_literal == l.bool_literal;
                if (type == Type::Integer)
                    return int_literal == l.int_literal;
            }
            return false;
        }
    };
}// namespace Bytecode
