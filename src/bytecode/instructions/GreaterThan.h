#pragma once

#include "bytecode/instructions/Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        void execute(Bytecode::VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \">\", Expected number, got string");
            }
            vm.program_stack.push(object1.data.number > object2.data.number);
        }
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
    };
}// namespace Bytecode
