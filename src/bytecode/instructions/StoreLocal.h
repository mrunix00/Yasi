#pragma once

#include "Instruction.h"
#include <string>

namespace Bytecode {
    class StoreLocal final : public Instruction {
    public:
        explicit StoreLocal(const size_t reg) {
            params.r_param = {reg};
            type = InstructionType::StoreLocal;
        }
        void execute(Bytecode::VM &vm) override {
            vm.call_stack.setLocal(params.r_param.reg, vm.program_stack.pop());
        }
        [[nodiscard]] std::string toString() const override {
            return "StoreLocal $r" + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
