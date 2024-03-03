#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Not final : public Instruction {
    public:
        Not() {
            type = InstructionType::Not;
        }

        void execute(VM *vm) override {
            const auto object = vm->program_stack.pop();
            vm->program_stack.push(!object.asBoolean());
        }

        [[nodiscard]] std::string toString() const override {
            return "Not";
        }

        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode