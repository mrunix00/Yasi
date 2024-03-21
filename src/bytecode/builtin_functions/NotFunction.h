#pragma once

#include "Function.h"
#include "bytecode/instructions/Not.h"

namespace Bytecode::BuiltinFunctions {
    class Not final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (args.size() != 1) {
                throw SyntaxError("Invalid number of arguments for function \"not\", Expected 1, got "
                                  + std::to_string(args.size()));
            }
            args[0]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Not());
        }
    };
}// namespace Bytecode::BuiltinFunctions