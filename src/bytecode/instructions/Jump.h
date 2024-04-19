#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Jump final : public Instruction {
    public:
        explicit Jump(const size_t line) {
            params.r_param.reg = line;
            type = InstructionType::Jump;
        }
        void execute(Bytecode::VM &vm) override {
            vm.call_stack.stackTop->current_line = params.r_param.reg - 1;
        }
        [[nodiscard]] std::string toString() const override {
            return "Jump " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
