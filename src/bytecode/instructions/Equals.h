#ifndef YASI_EQUALS_H
#define YASI_EQUALS_H

#include "Instruction.h"

namespace Bytecode {
    class Equals : public Instruction {
    public:
        Equals() { type = InstructionType::Equals; };
        [[nodiscard]] std::string toString() const override { return "Equals"; }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}
#endif//YASI_EQUALS_H
