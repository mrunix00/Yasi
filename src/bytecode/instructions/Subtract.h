#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_SUBTRACT_H
