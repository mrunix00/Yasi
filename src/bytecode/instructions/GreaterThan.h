#ifndef YASI_GREATERTHAN_H
#define YASI_GREATERTHAN_H

#include "Instruction.h"

namespace Bytecode {
    class GreaterThan final : public Instruction {
    public:
        GreaterThan() { type = InstructionType::GreaterThan; };
        [[nodiscard]] std::string toString() const override { return "GreaterThan"; }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}

#endif//YASI_GREATERTHAN_H
