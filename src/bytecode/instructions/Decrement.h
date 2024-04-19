#include "Instruction.h"

namespace Bytecode {
    class Decrement final : public Instruction {
    public:
        Decrement() { type = InstructionType::Decrement; };
        [[nodiscard]] std::string toString() const override { return "Decrement"; }
    };
}// namespace Bytecode