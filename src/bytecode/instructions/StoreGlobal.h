#pragma once

#include "Instruction.h"
#include <string>

namespace Bytecode {
    class StoreGlobal final : public Instruction {
    public:
        explicit StoreGlobal(const size_t reg) {
            params.r_param = {reg};
            type = InstructionType::StoreGlobal;
        }
        void execute(Bytecode::VM &vm) override {
            vm.setGlobal(params.r_param.reg, vm.program_stack.pop());
        }
        [[nodiscard]] std::string toString() const override {
            return "Store $r" + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
