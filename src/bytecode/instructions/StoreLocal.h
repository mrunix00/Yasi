#pragma once

#include "Instruction.h"
#include "bytecode/objects/Register.h"
#include <string>

namespace Bytecode {
    class StoreLocal final : public Instruction {
        size_t reg;

    public:
        explicit StoreLocal(size_t reg) : reg(reg) {
            type = InstructionType::StoreLocal;
        }

        void execute(VM *vm) override {
            vm->call_stack.setLocal(0, vm->program_stack.pop());
        }
        [[nodiscard]] std::string toString() const override {
            return "StoreLocal $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const StoreLocal *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
