#pragma once

#include "Instruction.h"

namespace Bytecode {
    class DecrementR final : public Instruction {
    public:
        explicit DecrementR(size_t reg) {
            params.r_param = {reg};
            type = InstructionType::DecrementR;
        }
        void execute(Bytecode::VM &vm) override {
            double number = vm.call_stack.getLocal(params.r_param.reg).asNumber();
            vm.program_stack.push(number - 1);
        }
        [[nodiscard]] std::string toString() const override {
            return "DecrementR $r" + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode