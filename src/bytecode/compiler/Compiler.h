#ifndef YASI_COMPILER_H
#define YASI_COMPILER_H

#include "Program.h"
#include "Segment.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"
#include <unordered_map>

namespace Bytecode {
    class Compiler {
    public:
        Compiler() = default;
        void compile(const SyntaxTreeNode &, Segment *, std::vector<Instruction *> &);
        void compile(const SyntaxTreeNode &, Segment *);
        void compile(const SyntaxTreeNode &);
        Program program;
    };
}// namespace Bytecode
#endif