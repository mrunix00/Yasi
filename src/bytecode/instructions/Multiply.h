#ifndef YASI_MULTIPLY_H
#define YASI_MULTIPLY_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_MULTIPLY_H
