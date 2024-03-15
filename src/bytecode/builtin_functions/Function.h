#pragma once

#include "parser/SyntaxTreeNode.h"
#include <vector>

namespace Bytecode::BuiltinFunctions {
    class Function {
    public:
        virtual ~Function() = default;
        virtual void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *) = 0;
    };
}// namespace Bytecode::BuiltinFunctions
