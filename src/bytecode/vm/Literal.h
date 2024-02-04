#ifndef YASI_LITERAL_H
#define YASI_LITERAL_H

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

        explicit Literal(bool b) : bool_literal(b ? Boolean::True : Boolean::False),
                                   type(Type::Boolean) {}
        explicit Literal(Boolean b) : bool_literal(b), type(Type::Boolean) {}
        explicit Literal(int val) : int_literal(val), type(Type::Integer) {}

        inline bool operator==(Literal l) const {
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

#endif//YASI_LITERAL_H
