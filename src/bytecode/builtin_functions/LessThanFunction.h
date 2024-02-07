#pragma once

#include "Function.h"
#include "bytecode/instructions/LessThan.h"
namespace Bytecode::BuiltinFunctions {
    class LessThan : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
            compiler.compile(*args[0], result, instructions);
            compiler.compile(*args[1], result, instructions);
            instructions.push_back(new Bytecode::LessThan());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result, instructions);
                instructions.push_back(new Bytecode::LessThan());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
