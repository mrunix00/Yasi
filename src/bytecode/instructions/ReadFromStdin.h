#pragma once
#include "Instruction.h"

namespace Bytecode {
    class ReadFromStdin final : public Instruction {
    public:
        explicit ReadFromStdin() {
            type = InstructionType::ReadFromStdin;
        }
        [[nodiscard]] std::string toString() const override { return "ReadFromStdin"; }
    };
}// namespace Bytecode