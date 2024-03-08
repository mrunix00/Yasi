#pragma once

#include "./Function.h"
#include "bytecode/compiler/CompilerUtils.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/LoadLiteral.h"

namespace Bytecode::BuiltinFunctions {
    class Add final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (compiler.optimization && is_optimizable(args)) {
                double result = 0;
                for (const auto arg: args) {
                    if (!arg->children.empty()) {
                        auto part = std::vector<Instruction *>();
                        compiler.compile(*arg, segment, part);
                        result += (((LoadLiteral *) part[0])->literal).asNumber();
                    } else {
                        result += arg->token.asNumber();
                    }
                }
                instructions.push_back(new LoadLiteral(result));
                return;
            }
            compiler.compile(*args[0], segment, instructions);
            compiler.compile(*args[1], segment, instructions);
            instructions.push_back(new Bytecode::Add());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], segment, instructions);
                instructions.push_back(new Bytecode::Add());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
