#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Add; };
    };
}// namespace Bytecode

#endif//YASI_SUBTRACT_H
