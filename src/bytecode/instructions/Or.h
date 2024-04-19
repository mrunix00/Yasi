#pragma once

#include "Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class Or final : public Instruction {
    public:
        Or() {type = InstructionType::Or;}
        void execute(Bytecode::VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Boolean ||
                object2.type != ObjectType::Boolean) {
                throw SyntaxError("Invalid argument type for function \"or\", Expected boolean, got string");
            }
            vm.program_stack.push(object1.asBoolean() || object2.asBoolean());
        }
        [[nodiscard]] std::string toString() const override {
            return "Or";
        }
    };
}// namespace Bytecode