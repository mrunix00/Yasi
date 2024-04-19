#pragma once

#include "Instruction.h"
namespace Bytecode {
    class LessThanRI final : public Instruction {
    public:
        LessThanRI(size_t rg, double number) {
            params.ri_params = {.reg = rg, .intermediate = StackObject(number)};
            type = InstructionType::LessThanRI;
        }
        [[nodiscard]] std::string toString() const override {
            return "LessThanRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode