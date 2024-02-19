#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            const auto result = new StackObject(
                    new Literal(object2->literal->int_literal >
                                object1->literal->int_literal));
            delete object1;
            delete object2;
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
