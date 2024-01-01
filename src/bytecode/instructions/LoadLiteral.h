#ifndef YASI_LOADLITERAL_H
#define YASI_LOADLITERAL_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class LoadLiteral final : public Instruction {
        int value;

    public:
        explicit LoadLiteral(int integer) {
            type = InstructionType::LoadLiteral;
            value = integer;
        };

        bool operator==(const Instruction &instruction) const override {
            return getType() == type && ((LoadLiteral *) &instruction)->value == value;
        }
    };
}// namespace Bytecode
#endif