#include "Instruction.h"

namespace Bytecode {
    class Decrement final : public Instruction {
    public:
        Decrement() { type = InstructionType::Decrement; };
        [[nodiscard]] std::string toString() const override { return "Decrement"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode