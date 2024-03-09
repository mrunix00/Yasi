#pragma once
#include "Instruction.h"

namespace Bytecode {
    class SendToStdout final : public Instruction {
    public:
        explicit SendToStdout() {
            type = InstructionType::SendToStdout;
        }
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "SendToStdout";
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}