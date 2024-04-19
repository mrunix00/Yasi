#include "Instruction.h"

namespace Bytecode {
    class Increment final : public Instruction {
    public:
        Increment() { type = InstructionType::Increment; };
        [[nodiscard]] std::string toString() const override { return "Increment"; }
    };
}// namespace Bytecode