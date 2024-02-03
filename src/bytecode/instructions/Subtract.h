#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        void execute(Bytecode::VM *vm) override {
            auto object1 = vm->stackPop();
            auto object2 = vm->stackPop();
            auto result = new StackObject(
                    new Literal(object2->literal->int_literal -
                                object1->literal->int_literal));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_SUBTRACT_H
