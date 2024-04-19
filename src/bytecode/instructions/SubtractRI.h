#pragma once

#include "Instruction.h"

namespace Bytecode {
    class SubtractRI final : public Instruction {
    public:
        SubtractRI(uint32_t rg, double number) {
            params.ri_params = {.reg = rg, .intermediate = StackObject(number)};
            type = InstructionType::SubtractRI;
        }
        [[nodiscard]] std::string toString() const override {
            return "SubtractRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode