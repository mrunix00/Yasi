#pragma once

#include "Function.h"

namespace Bytecode::BuiltinFunctions {
    class Multiply final : public Function {
        void compile(const std::vector<SyntaxTreeNode *> &args,
                     Program &program,
                     std::vector<Instruction *> &instructions,
                     Segment *segment) override;
    };
}// namespace Bytecode::BuiltinFunctions
