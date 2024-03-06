#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        void execute(VM *vm) override {
            const auto object2 = vm->program_stack.pop();
            const auto object1 = vm->program_stack.pop();
            const bool result = object1.asNumber() == object2.asNumber();
            vm->program_stack.push(result);
        }
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
