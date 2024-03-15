#pragma once

#include "Function.h"
#include "bytecode/instructions/Equals.h"

namespace Bytecode::BuiltinFunctions {
    class Equals : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program& program,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            args[0]->compile(segment, program, instructions);
            args[1]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Equals());
            for (int i = 2; i < args.size(); i++) {
                args[i]->compile(segment, program, instructions);
                instructions.push_back(new Bytecode::Equals());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
