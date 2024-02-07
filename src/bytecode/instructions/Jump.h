#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Jump final : public Instruction {
        size_t line;

    public:
        explicit Jump(const size_t line) : line(line) { type = InstructionType::Jump; }
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Jump " + std::to_string(line);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const Jump *>(&instruction)->line == line;
        }
    };
}// namespace Bytecode
