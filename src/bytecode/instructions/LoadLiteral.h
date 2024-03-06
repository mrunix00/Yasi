#pragma once

#include "bytecode/instructions/Instruction.h"
#include <sstream>

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        StackObject *literal;

        explicit LoadLiteral(double value) {
            type = InstructionType::LoadLiteral;
            literal = new StackObject(value);
        };

        explicit LoadLiteral(const std::string &value) {
            type = InstructionType::LoadLiteral;
            literal = new StackObject(value);
        };

        explicit LoadLiteral(StackObject *literal) : literal(literal) {}

        void execute(VM *vm) override {
            vm->program_stack.push(*literal);
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
