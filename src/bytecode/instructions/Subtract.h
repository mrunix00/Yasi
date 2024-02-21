#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            const auto result =
                    ((NumberLiteral *) object2->literal)->asNumber() -
                    ((NumberLiteral *) object1->literal)->asNumber();
            delete object1;
            delete object2;
            vm->stackPush(new StackObject(new NumberLiteral(result)));
        }
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
