#ifndef YASI_ADD_H
#define YASI_ADD_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif