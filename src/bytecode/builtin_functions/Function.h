#pragma once

#include "bytecode/compiler/Compiler.h"
#include "parser/SyntaxTreeNode.h"
#include <vector>

namespace Bytecode::BuiltinFunctions {
    class Function {
    public:
        virtual ~Function() = default;
        virtual void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *) = 0;

    };
}// namespace Bytecode::BuiltinFunctions
