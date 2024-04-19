#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Call final : public Instruction {
    public:
        explicit Call(const size_t segment, const size_t args) {
            params.ri_params = {.reg = segment, .intermediate = StackObject(args)};
            type = InstructionType::Call;
        }
        [[nodiscard]] std::string toString() const override {
            return "Call :" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode
