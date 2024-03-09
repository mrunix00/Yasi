#pragma once

#include "bytecode/instructions/Instruction.h"
#include <sstream>

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        explicit LoadLiteral(const double value) {
            type = InstructionType::LoadLiteral;
            literal = StackObject(value);
        };

        explicit LoadLiteral(const std::string &value) {
            type = InstructionType::LoadLiteral;
            literal = StackObject(value);
        };

        explicit LoadLiteral(const StackObject *literal){
            this->literal = *literal;
        }

        [[nodiscard]] std::string toString() const override {
            return "LoadLiteral " + literal.toString();
        }

        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const LoadLiteral *>(&instruction)->literal == literal;
        }
    };
}// namespace Bytecode
