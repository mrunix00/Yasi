#pragma once

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class Subtract final : public Instruction {
    public:
        Subtract() { type = InstructionType::Subtract; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            if (object1->literal->type == Literal::Number &&
                object2->literal->type == Literal::Number) {
                const auto result =
                        ((NumberLiteral *) object2->literal)->asNumber() -
                        ((NumberLiteral *) object1->literal)->asNumber();
                vm->stackPush(new StackObject(new NumberLiteral(result)));
            } else {
                const auto result =
                        (object2->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object2->literal)->asNumber()) -
                        (object1->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object1->literal)->asNumber());
                vm->stackPush(new StackObject(new DecimalNumberLiteral(result)));
            }
            delete object1;
            delete object2;
        }
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
