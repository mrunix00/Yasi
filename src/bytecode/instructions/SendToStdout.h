#pragma once
#include "Instruction.h"

namespace Bytecode {
    class SendToStdout final : public Instruction {
    public:
        explicit SendToStdout() {
            type = InstructionType::SendToStdout;
        }
        [[nodiscard]] std::string toString() const override { return "SendToStdout"; }
    };
}// namespace Bytecode