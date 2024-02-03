#ifndef YASI_LITERAL_H
#define YASI_LITERAL_H

namespace Bytecode {
    class Literal {
    public:
        explicit Literal(int val) : int_literal(val) {}

        inline bool operator==(Literal l) const {
            return int_literal == l.int_literal;
        }
        int int_literal;
    };
}// namespace Bytecode

#endif//YASI_LITERAL_H
