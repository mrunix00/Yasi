#pragma once

#include "Function.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/objects/GlobalRegister.h"

namespace Bytecode::BuiltinFunctions {
    class Define final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
            if (args[1]->children.empty()) {
                compiler.compile(*args[1], result, instructions);
                const auto reg = compiler.program.declare_global(args[0]->token.token);
                instructions.push_back(new Store(new GlobalRegister(reg)));
            } else {
                auto segment = new Segment({});
                compiler.program.declare_function(args[0]->token.asString(), segment);
                for (auto argument: args[0]->children)
                    segment->declare_variable(argument->token.asString());
                compiler.compile(*args[1], segment);
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
