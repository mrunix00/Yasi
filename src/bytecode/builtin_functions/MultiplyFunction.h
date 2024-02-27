#pragma once

#include "Function.h"
#include "bytecode/compiler/CompilerUtils.h"
#include "bytecode/instructions/Multiply.h"

namespace Bytecode::BuiltinFunctions {
    class Multiply final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (compiler.optimization && is_optimizable(args)) {
                int64_t result = 1;
                for (const auto arg: args) {
                    if (!arg->children.empty()) {
                        auto part = std::vector<Instruction *>();
                        compiler.compile(*arg, segment, part);
                        result *= ((NumberLiteral*) static_cast<LoadLiteral *>(part[0])->literal)->asNumber();
                    } else {
                        result *= arg->token.asInteger();
                    }
                }
                instructions.push_back(new LoadLiteral(result));
            } else {
                compiler.compile(*args[0], segment, instructions);
                compiler.compile(*args[1], segment, instructions);
                instructions.push_back(new Bytecode::Multiply());
                for (int i = 2; i < args.size(); i++) {
                    compiler.compile(*args[i], segment, instructions);
                    instructions.push_back(new Bytecode::Multiply());
                }
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
