#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Call final : public Instruction {
    public:
        explicit Call(const size_t segment, const size_t args) {
            this->reg = segment;
            this->param = args;
            type = InstructionType::Call;
        }
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Call :" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   instruction.reg == reg &&
                   instruction.param == param;
        }
    };
}// namespace Bytecode
