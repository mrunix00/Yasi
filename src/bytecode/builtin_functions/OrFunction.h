#pragma once

#include "Function.h"
#include "bytecode/instructions/Or.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    class Or final : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *segment) override {
            if (args.empty()) throw SyntaxError(
                    "Invalid number of arguments for function \"or\", Expected at least 1, got 0");
            args[0]->compile(segment, program, instructions);
            if (args.size() == 1) return;
            args[1]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Or());
            for (int i = 2; i < args.size(); i++) {
                args[i]->compile(segment, program, instructions);
                instructions.push_back(new Bytecode::Or());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions