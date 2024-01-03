#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}// namespace Bytecode

#endif//YASI_SUBTRACT_H
