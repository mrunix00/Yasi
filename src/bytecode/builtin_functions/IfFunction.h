#pragma once

#include "Function.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/Jump.h"

namespace Bytecode::BuiltinFunctions {
    class If : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Program &program,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
            std::vector<Instruction *> condition_success;
            std::vector<Instruction *> condition_failure;
            args[0]->compile(result, program, instructions);

            args[1]->compile(result, program, condition_success);
            if (args.size() == 3)
                args[2]->compile(result, program, condition_failure);

            result->instructions.push_back(
                    new CondJumpIfNot(
                            result->instructions.size() + condition_success.size() +
                            (condition_failure.empty() ? 1 : 2)));
            for (const auto instruction: condition_success)
                instructions.push_back(instruction);
            if (!condition_failure.empty())
                instructions.push_back(new Jump(instructions.size() + condition_failure.size() + 1));

            for (const auto instruction: condition_failure)
                instructions.push_back(instruction);
        }
    };
}// namespace Bytecode::BuiltinFunctions
