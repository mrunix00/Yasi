#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            if (object1->literal->type == Literal::Number &&
                object2->literal->type == Literal::Number) {
                const auto result =
                        ((NumberLiteral *) object1->literal)->asNumber() *
                        ((NumberLiteral *) object2->literal)->asNumber();
                vm->stackPush(new StackObject(new NumberLiteral(result)));
            } else {
                const auto result =
                        (object1->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object1->literal)->asNumber()) *
                        (object2->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object2->literal)->asNumber());
                vm->stackPush(new StackObject(new DecimalNumberLiteral(result)));
            }
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
