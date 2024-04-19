#pragma once

#include "Instruction.h"

namespace Bytecode {
    class AddRI final : public Instruction {
    public:
        AddRI(uint32_t rg, double number) {
            type = InstructionType::AddRI;
            params = {rg, StackObject(number)};
        }
        [[nodiscard]] std::string toString() const override {
            return "AddRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode