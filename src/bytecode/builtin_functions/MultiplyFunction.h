#ifndef YASI_MULTIPLY_FUNCTION_H
#define YASI_MULTIPLY_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/Multiply.h"

static bool is_multiplication_optimizable(const std::vector<SyntaxTreeNode *> &args) {
    return std::all_of(args.begin(), args.end(), [](const SyntaxTreeNode *arg) {
        if (!arg->children.empty()) {
            if (!is_addition_optimizable(arg->children)) return false;
        } else {
            return arg->token->type != Token::Symbol;
        }
        return true;
    });
}

namespace Bytecode::BuiltinFunctions {
    class Multiply final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (compiler.optimization && is_multiplication_optimizable(args)) {
                int result = 1;
                for (const auto arg: args) {
                    if (!arg->children.empty()) {
                        auto part = std::vector<Instruction *>();
                        compiler.compile(*arg, segment, part);
                        result *= static_cast<LoadLiteral *>(part[0])->value;
                    } else {
                        result *= arg->token->asInteger();
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

#endif//YASI_MULTIPLY_FUNCTION_H
