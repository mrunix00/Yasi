#ifndef YASI_ADD_H
#define YASI_ADD_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}// namespace Bytecode

#endif