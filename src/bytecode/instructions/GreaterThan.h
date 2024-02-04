#ifndef YASI_GREATERTHAN_H
#define YASI_GREATERTHAN_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        void execute(Bytecode::VM *vm) override {
            auto object1 = vm->stackPop();
            auto object2 = vm->stackPop();
            auto result = new StackObject(
                    new Literal(object2->literal->int_literal >
                                                object1->literal->int_literal
                                        ? Boolean::True
                                        : Boolean::False));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode

#endif//YASI_GREATERTHAN_H
