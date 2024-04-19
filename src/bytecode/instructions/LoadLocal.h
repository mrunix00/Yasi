#pragma once

#include "Instruction.h"

namespace Bytecode {
    class LoadLocal final : public Instruction {
    public:
        explicit LoadLocal(const size_t reg) {
            type = InstructionType::LoadLocal;
            params.r_param = {reg};
        }

        [[nodiscard]] std::string toString() const override {
            return "LoadLocal $r" + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode
