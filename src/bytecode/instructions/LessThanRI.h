#pragma once

#include "Instruction.h"
namespace Bytecode {
    class LessThanRI final : public Instruction {
    public:
        LessThanRI(size_t rg, double number) {
            params.ri_params = {.reg = rg, .intermediate = StackObject(number)};
            type = InstructionType::LessThanRI;
        }
        void execute(Bytecode::VM &vm) override {
            const auto object2 =params.ri_params.intermediate;
            const auto object1 = vm.call_stack.getLocal(params.ri_params.reg);
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"<\", Expected number, got string");
            }
            vm.program_stack.push(object1.asNumber() < object2.asNumber());
        }
        [[nodiscard]] std::string toString() const override {
            return "LessThanRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode