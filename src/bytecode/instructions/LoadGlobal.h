#pragma once

#include "Instruction.h"

namespace Bytecode {
    class LoadGlobal final : public Instruction {
    public:
        explicit LoadGlobal(const uint32_t reg) {
            params.r_param = {reg};
            type = InstructionType::LoadGlobal;
        }

        [[nodiscard]] std::string toString() const override {
            return "LoadGlobal $g" + std::to_string(params.r_param.reg);
        }
    };
}