#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        explicit LoadLiteral(const int integer) {
            type = InstructionType::LoadLiteral;
            value = integer;
        };
        void execute(VM *vm) override {
            vm->stackPush(new StackObject(new Literal(value)));
        }
        [[nodiscard]] std::string toString() const override {
            return "LoadLiteral d" + std::to_string(value);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const LoadLiteral *>(&instruction)->value == value;
        }
        int value;
    };
}// namespace Bytecode
