#ifndef YASI_LESSTHAN_H
#define YASI_LESSTHAN_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class LessThan final : public Instruction {
    public:
        LessThan() { type = InstructionType::LessThan; };
        void execute(Bytecode::VM *vm) override {
            auto object1 = vm->stackPop();
            auto object2 = vm->stackPop();
            auto result = new StackObject(
                    new Literal(object2->literal->int_literal <
                                object1->literal->int_literal));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "LessThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_LESSTHAN_H
