#ifndef YASI_EQUALS_H
#define YASI_EQUALS_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        void execute(Bytecode::VM *vm) override {
            auto object1 = vm->stackPop();
            auto object2 = vm->stackPop();
            auto result = new StackObject(
                    new Literal(object1->literal->int_literal ==
                                                object2->literal->int_literal
                                        ? Boolean::True
                                        : Boolean::False));
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
#endif//YASI_EQUALS_H
