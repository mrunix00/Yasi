#pragma once

#include "Function.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/SendToStdout.h"

namespace Bytecode::BuiltinFunctions {
    class Print final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            for (const auto arg: args) {
                arg->compile(segment, program, instructions);
                instructions.push_back(new SendToStdout());
            }
            instructions.push_back(new LoadLiteral("\n"));
            instructions.push_back(new SendToStdout());
        };
    };
}// namespace Bytecode::BuiltinFunctions
