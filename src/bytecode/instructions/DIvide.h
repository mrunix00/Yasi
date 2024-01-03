#ifndef YASI_DIVIDE_H
#define YASI_DIVIDE_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}// namespace Bytecode

#endif//YASI_DIVIDE_H
