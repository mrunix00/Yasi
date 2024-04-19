#pragma once

#include "Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class And final : public Instruction {
    public:
        And() {type = InstructionType::And;}
        void execute(Bytecode::VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Boolean ||
                object2.type != ObjectType::Boolean) {
                throw SyntaxError("Invalid argument type for function \"and\", Expected boolean, got string");
            }
            vm.program_stack.push(object1.asBoolean() && object2.asBoolean());
        }
        [[nodiscard]] std::string toString() const override {
            return "And";
        }
    };
}// namespace Bytecode