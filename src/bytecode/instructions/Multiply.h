#pragma once

#include "bytecode/instructions/Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class Multiply final : public Instruction {
    public:
        Multiply() { type = InstructionType::Multiply; };
        void execute(VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"*\", Expected number, got string");
            }
            vm.program_stack.push(object1.asNumber() * object2.asNumber());
        }
        [[nodiscard]] std::string toString() const override { return "Multiply"; }
    };
}// namespace Bytecode
