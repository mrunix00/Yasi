#pragma once

#include "Instruction.h"

namespace Bytecode {
    class SubtractRI final : public Instruction {
    public:
        SubtractRI(uint32_t rg, double number) {
            params.ri_params = {.reg = rg, .intermediate = StackObject(number)};
            type = InstructionType::SubtractRI;
        }
        void execute(VM &vm) override {
            const auto object2 = params.ri_params.intermediate;
            const auto object1 = vm.call_stack.getLocal(params.ri_params.reg);
            if (object1.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
            }
            vm.program_stack.push(object1.data.number - object2.data.number);
        }
        [[nodiscard]] std::string toString() const override {
            return "SubtractRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode