#ifndef YASI_COMPILER_H
#define YASI_COMPILER_H

#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Compiler {
    public:
        static void compile(const SyntaxTreeNode &, std::vector<Instruction> &);
    };
}
#endif