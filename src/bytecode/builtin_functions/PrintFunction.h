#pragma once

#include "Function.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/objects/StdOutRegister.h"

namespace Bytecode::BuiltinFunctions {
    class Print final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            for (const auto arg: args) {
                compiler.compile(*arg, segment, instructions);
                instructions.push_back(new Store(new StdOutRegister()));
            }
            instructions.push_back(new LoadLiteral("\n"));
            instructions.push_back(new Store(new StdOutRegister()));
        };
    };
}// namespace Bytecode::BuiltinFunctions
