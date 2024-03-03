#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            auto *result = new NumberLiteral(
                    ((NumberLiteral *) object2)->asNumber() +
                    ((NumberLiteral *) object1)->asNumber());
            delete object1;
            delete object2;
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
