#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/DecimalNumberLiteral.h"
#include "bytecode/objects/NumberLiteral.h"


namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        void execute(VM *vm) override {
            const auto object1 = vm->stackPop();
            const auto object2 = vm->stackPop();
            float result =
                    (object2->literal->type == Literal::DecimalNumber
                             ? ((DecimalNumberLiteral *) object2->literal)->asDecimalNumber()
                             : (float) ((NumberLiteral *) object2->literal)->asNumber()) /
                    (object1->literal->type == Literal::DecimalNumber
                             ? ((DecimalNumberLiteral *) object1->literal)->asDecimalNumber()
                             : (float) ((NumberLiteral *) object1->literal)->asNumber());

            vm->stackPush(new StackObject(new DecimalNumberLiteral(result)));
        }
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode
