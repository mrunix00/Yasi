#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/BooleanLiteral.h"
#include "bytecode/objects/NumberLiteral.h"
#include "bytecode/objects/DecimalNumberLiteral.h"

namespace Bytecode {
    class LessThan final : public Instruction {
    public:
        LessThan() { type = InstructionType::LessThan; };
        void execute(VM *vm) override {
            const auto object2 = vm->stackPop();
            const auto object1 = vm->stackPop();
            bool result;
            if (object1->literal->type == Literal::Type::Number &&
                object2->literal->type == Literal::Type::Number) {
                result = ((NumberLiteral *) object1->literal)->asNumber() < ((NumberLiteral *) object2->literal)->asNumber();
            } else {
                result = (object1->literal->type == Literal::DecimalNumber
                                  ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                                  : (float) ((NumberLiteral *) object1->literal)->asNumber()) <
                         (object2->literal->type == Literal::DecimalNumber
                                  ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                                  : (float) ((NumberLiteral *) object2->literal)->asNumber());
            }
            delete object1;
            delete object2;
            vm->stackPush(new StackObject(new BooleanLiteral(result)));
        }
        [[nodiscard]] std::string toString() const override { return "LessThan"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
