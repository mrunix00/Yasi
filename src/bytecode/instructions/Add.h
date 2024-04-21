#pragma once

#include "bytecode/instructions/Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class Add final : public Instruction {
    public:
        Add() { type = InstructionType::Add; }
        void execute(Bytecode::VM &vm) override {
            const auto object2 = vm.program_stack.pop();
            const auto object1 = vm.program_stack.pop();
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
            }
            vm.program_stack.push(object1.data.number + object2.data.number);
        }
        [[nodiscard]] std::string toString() const override { return "Add"; }
    };
}// namespace Bytecode
