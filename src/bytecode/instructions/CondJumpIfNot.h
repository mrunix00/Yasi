#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CondJumpIfNot final : public Instruction {
    public:
        explicit CondJumpIfNot(const size_t line) {
            params.r_param = {line};
            type = InstructionType::CondJumpIfNot;
        }
        void execute(Bytecode::VM &vm) override {
            if (const auto cond = vm.program_stack.pop();
                !cond.asBoolean())
                vm.call_stack.stackTop->current_line = params.r_param.reg - 1;
        }
        [[nodiscard]] std::string toString() const override {
            return "CondJumpIfNot " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
