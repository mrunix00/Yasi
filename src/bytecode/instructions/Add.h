#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/DecimalNumberLiteral.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            StackObject *result;
            if (object1->literal->type == Literal::Number &&
                object2->literal->type == Literal::Number) {
                result = new StackObject(new NumberLiteral(
                        ((NumberLiteral *) object2->literal)->asNumber() +
                        ((NumberLiteral *) object1->literal)->asNumber()));
            } else {
                result = new StackObject(new DecimalNumberLiteral(
                        (object2->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object2->literal)->asNumber()) +
                        (object1->literal->type == Literal::DecimalNumber
                                 ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                                 : ((NumberLiteral *) object1->literal)->asNumber())));
            }
            delete object1;
            delete object2;
            vm->stackPush(result);
        }
        [[nodiscard]] std::string toString() const override { return "Add"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
