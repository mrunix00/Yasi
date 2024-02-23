#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/BooleanLiteral.h"
#include "bytecode/objects/DecimalNumberLiteral.h"
#include "bytecode/objects/NumberLiteral.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            bool result;
            if (object1->literal->type == Literal::Type::Number &&
                object2->literal->type == Literal::Type::Number) {
                result = ((NumberLiteral *) object1->literal)->asNumber() == ((NumberLiteral *) object2->literal)->asNumber();
            } else {
                result = (object1->literal->type == Literal::DecimalNumber
                                  ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                                  : (float) ((NumberLiteral *) object1->literal)->asNumber()) ==
                         (object2->literal->type == Literal::DecimalNumber
                                  ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                                  : (float) ((NumberLiteral *) object2->literal)->asNumber());
            }
            delete object1;
            delete object2;
            vm->stackPush(new StackObject(new BooleanLiteral(result)));
        }
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
