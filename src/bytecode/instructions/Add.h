#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        void execute(VM *vm) override {
            const auto object2 = vm->program_stack.pop();
            const auto object1 = vm->program_stack.pop();
            double result = object1.asNumber() + object2.asNumber();
            vm->program_stack.push(result);
        }
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
