#pragma once

#include "Function.h"
#include "bytecode/instructions/SendToStdout.h"

namespace Bytecode::BuiltinFunctions {
    class Print final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            for (const auto arg: args) {
                compiler.compile(*arg, segment, instructions);
                instructions.push_back(new SendToStdout());
            }
            instructions.push_back(new LoadLiteral("\n"));
            instructions.push_back(new SendToStdout());
        };
    };
}// namespace Bytecode::BuiltinFunctions
