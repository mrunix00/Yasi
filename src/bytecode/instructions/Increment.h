#include "Instruction.h"

namespace Bytecode {
    class Increment final : public Instruction {
    public:
        Increment() { type = InstructionType::Increment; };
        [[nodiscard]] std::string toString() const override { return "Increment"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}// namespace Bytecode