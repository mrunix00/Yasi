#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/BooleanLiteral.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class LessThan final : public Instruction {
    public:
        LessThan() { type = InstructionType::LessThan; };
        void execute(VM *vm) override {
            const auto object2 = vm->stackPop();
            const auto object1 = vm->stackPop();
            auto *result = new BooleanLiteral(
                    ((NumberLiteral *) object1)->asNumber() <
                    ((NumberLiteral *) object2)->asNumber());
            vm->stackPush(result);
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "LessThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
