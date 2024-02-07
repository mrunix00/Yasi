#pragma once

#include "Program.h"
#include "Segment.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Compiler {
    public:
        bool optimization = false;
        Compiler() = default;
        explicit Compiler(const bool optimize) : optimization(optimize){};
        void compile(const SyntaxTreeNode &, Segment *, std::vector<Instruction *> &);
        void compile(const SyntaxTreeNode &, Segment *);
        void compile(const SyntaxTreeNode &);
        Program program;
    };
}// namespace Bytecode