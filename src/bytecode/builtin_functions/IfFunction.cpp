#include "IfFunction.h"

namespace Bytecode::BuiltinFunctions {
    void If::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *result) {
        std::vector<Instruction *> condition_success;
        std::vector<Instruction *> condition_failure;
        args[0]->compile(result, program, instructions);

        args[1]->compile(result, program, condition_success);
        if (args.size() == 3)
            args[2]->compile(result, program, condition_failure);
        result->instructions.push_back(new (Instruction){
                Instruction::CondJumpIfNot,
                {.r_param = {result->instructions.size() + condition_success.size() +
                             (condition_failure.empty() ? 1 : 2)}},
        });
        for (const auto instruction: condition_success)
            instructions.push_back(instruction);
        if (!condition_failure.empty())
            instructions.push_back(new (Instruction) {
                    Instruction::Jump,
                    {.r_param = {instructions.size() + condition_failure.size() + 1}},
            });

        for (const auto instruction: condition_failure)
            instructions.push_back(instruction);
    }
}// namespace Bytecode::BuiltinFunctions