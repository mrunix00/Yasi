#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Not final : public Instruction {
    public:
        Not() {
            type = InstructionType::Not;
        }

        void execute(VM *vm) override {
            const auto object = vm->stackPop();
            const auto boolean = ((BooleanLiteral *) object->literal)->asBoolean();
            const auto return_object = new StackObject(new BooleanLiteral(!boolean));
            vm->stackPush(return_object);
        }

        [[nodiscard]] std::string toString() const override {
            return "Not";
        }

        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode