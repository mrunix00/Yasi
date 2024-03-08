#pragma once

#include "Instruction.h"
#include "bytecode/objects/Register.h"
#include <string>

namespace Bytecode {
    class StoreGlobal final : public Instruction {
        size_t reg;

    public:
        explicit StoreGlobal(size_t reg) : reg(reg) {
            type = InstructionType::StoreGlobal;
        }

        void execute(VM *vm) override {
            vm->setGlobal(0, vm->program_stack.pop());
        }
        [[nodiscard]] std::string toString() const override {
            return "Store $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const StoreGlobal *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
