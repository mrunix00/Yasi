#pragma once

#include "Instruction.h"
#include <string>

namespace Bytecode {
    class Store final : public Instruction {
        size_t reg;

    public:
        explicit Store(const size_t rg) {
            reg = rg;
            type = InstructionType::Store;
        }
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Store $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const Store *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
