#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/BooleanLiteral.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            auto *result = new StackObject(new BooleanLiteral(
                    ((NumberLiteral *) object2->literal)->asNumber() ==
                    ((NumberLiteral *) object1->literal)->asNumber()));
            vm->stackPush(result);
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
