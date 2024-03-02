#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            auto *result = new StackObject(new NumberLiteral(
                    ((NumberLiteral *) object2->literal)->asNumber() /
                    ((NumberLiteral *) object1->literal)->asNumber()));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
