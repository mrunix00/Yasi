#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        void execute(VM *vm) override {
            const auto object2 = vm->stackPop();
            const auto object1 = vm->stackPop();
            auto *result = new NumberLiteral(
                    ((NumberLiteral *) object1)->asNumber() -
                    ((NumberLiteral *) object2)->asNumber());
            vm->stackPush(result);
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
