#pragma once

#include "Function.h"
#include "bytecode/instructions/ReadFromStdin.h"
namespace Bytecode::BuiltinFunctions {
    class Read : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (!args.empty()) {
                throw SyntaxError(
                        "Invalid number of arguments for function \"read\", Expected 0, got " +
                        std::to_string(args.size()));
            }
            instructions.push_back(new ReadFromStdin());
        };
    };
}// namespace Bytecode::BuiltinFunctions