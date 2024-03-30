#pragma once

#include "Function.h"

namespace Bytecode::BuiltinFunctions {
    class If : public Function {
        void compile(const std::vector<SyntaxTreeNode *> &args,
                     Program &program,
                     std::vector<Instruction *> &instructions,
                     Segment *result) override;
    };
}// namespace Bytecode::BuiltinFunctions
