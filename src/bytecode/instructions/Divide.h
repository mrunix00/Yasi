#ifndef YASI_DIVIDE_H
#define YASI_DIVIDE_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_DIVIDE_H
