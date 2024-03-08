#pragma once

#include "Instruction.h"
#include "bytecode/objects/LocalRegister.h"
#include "bytecode/objects/Register.h"

namespace Bytecode {
    class LoadLocal final : public Instruction {
        size_t reg;

    public:
        explicit LoadLocal(size_t reg) : reg(reg) {
            type = InstructionType::Load;
        }

        void execute(VM *vm) override {
            vm->program_stack.push(vm->call_stack.getLocal(reg));
        }

        [[nodiscard]] std::string toString() const override {
            return "LoadLocal $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const LoadLocal *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
