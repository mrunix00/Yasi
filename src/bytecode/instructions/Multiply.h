#ifndef YASI_MULTIPLY_H
#define YASI_MULTIPLY_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        void execute(Bytecode::VM *vm) override {
            auto object1 = vm->stackPop();
            auto object2 = vm->stackPop();
            auto result = new StackObject(
                    new Literal(object1->literal->int_literal *
                                object2->literal->int_literal));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_MULTIPLY_H
