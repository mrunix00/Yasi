#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Jump final : public Instruction {
    public:
        explicit Jump(const size_t line) {
            this->param = line;
            type = InstructionType::Jump;
        }
        [[nodiscard]] std::string toString() const override {
            return "Jump " + std::to_string(param);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const Jump *>(&instruction)->param == param;
        }
    };
}// namespace Bytecode
