#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        Literal *literal;

        explicit LoadLiteral(int64_t integer) {
            type = InstructionType::LoadLiteral;
            literal = new NumberLiteral(integer);
        };

        void execute(VM *vm) override {
            vm->stackPush(new StackObject(literal->copy()));
        }
        [[nodiscard]] std::string toString() const override {
            return "LoadLiteral " + literal->toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   *(dynamic_cast<const LoadLiteral *>(&instruction)->literal) == *literal;
        }
    };
}// namespace Bytecode
