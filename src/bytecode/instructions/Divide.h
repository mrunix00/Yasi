#pragma once

#include "bytecode/instructions/Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class Divide final : public Instruction {
    public:
        Divide() { type = InstructionType::Divide; };
        void execute(Bytecode::VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"/\", Expected number, got string");
            }
            if (object2.asNumber() == 0) {
                throw SyntaxError("Division by zero", 0, 0);
            }
            vm.program_stack.push(object1.asNumber() / object2.asNumber());
        }
        [[nodiscard]] std::string toString() const override { return "Divide"; }
    };
}// namespace Bytecode
