#pragma once

#include "Function.h"
#include "bytecode/instructions/Not.h"

namespace Bytecode::BuiltinFunctions {
class Not final : public Function {
    void compile(
            const std::vector<SyntaxTreeNode *> &args,
            Compiler &compiler,
            std::vector<Instruction *> &instructions,
            Segment *segment
            ) override {
        compiler.compile(*args[0], segment, instructions);
        instructions.push_back(new Bytecode::Not());
    }
};
}