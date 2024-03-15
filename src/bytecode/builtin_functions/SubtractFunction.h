#pragma once

#include "Function.h"
#include "bytecode/instructions/Subtract.h"

namespace Bytecode::BuiltinFunctions {
    class Subtract : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
            args[0]->compile(result, program, instructions);
            args[1]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Subtract());
            for (int i = 2; i < args.size(); i++) {
                args[i]->compile(result, program, instructions);
                instructions.push_back(new Bytecode::Subtract());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
