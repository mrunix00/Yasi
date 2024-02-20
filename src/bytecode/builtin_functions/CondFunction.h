#pragma once

#include "Function.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/Jump.h"

namespace Bytecode::BuiltinFunctions {
    class Cond : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
            typedef std::vector<Instruction *> fresh_instructions;
            std::vector<fresh_instructions> conditions;
            std::vector<fresh_instructions> cond_success;
            fresh_instructions default_case;

            for (size_t i = 0; i < args.size() && (args.size() - i) >= 2; i += 2) {
                fresh_instructions condition;
                fresh_instructions condition_success;
                compiler.compile(*args[i], result, condition);
                compiler.compile(*args[i + 1], result, condition_success);
                conditions.push_back(condition);
                cond_success.push_back(condition_success);
            }

            if (args.size() % 2) {
                compiler.compile(*args.back(), result, default_case);
            }

            size_t end = instructions.size() + default_case.size() - default_case.empty();
            for (size_t i = 0; i < conditions.size(); i++) {
                end += conditions[i].size();
                end += cond_success[i].size();
                end += 2;
            }

            for (size_t i = 0; i < conditions.size(); i++) {
                for (const auto instruction: conditions[i])
                    result->instructions.push_back(instruction);
                result->instructions.push_back(
                        new CondJumpIfNot(
                                result->instructions.size() +
                                cond_success[i].size() +
                                2 - default_case.empty()));

                for (const auto instruction: cond_success[i])
                    result->instructions.push_back(instruction);

                if (!default_case.empty())
                    result->instructions.push_back(new Jump(end));
            }

            for (const auto instruction: default_case)
                result->instructions.push_back(instruction);
        }
    };
}// namespace Bytecode::BuiltinFunctions
