#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        void execute(VM *vm) override {
            const auto object2 = vm->stackPop();
            const auto object1 = vm->stackPop();
            auto *result = new NumberLiteral(
                    ((NumberLiteral *) object2)->asNumber() *
                    ((NumberLiteral *) object1)->asNumber());
            vm->stackPush(result);
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
