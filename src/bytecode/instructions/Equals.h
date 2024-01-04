#ifndef YASI_EQUALS_H
#define YASI_EQUALS_H

#include "Instruction.h"

namespace Bytecode {
    class Equals final : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
    };
}
#endif//YASI_EQUALS_H
