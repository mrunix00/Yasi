#ifndef YASI_ADD_H
#define YASI_ADD_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif