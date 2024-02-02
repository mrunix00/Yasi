#ifndef YASI_LITERAL_H
#define YASI_LITERAL_H

namespace Bytecode {
    class Literal {
        int int_literal;
    public:
        explicit Literal(int val) : int_literal(val) {}

        inline bool operator==(Literal l) const {
            return int_literal == l.int_literal;
        }
    };
}// namespace Bytecode

#endif//YASI_LITERAL_H
