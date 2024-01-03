#ifndef YASI_LESSTHAN_H
#define YASI_LESSTHAN_H

#include "Instruction.h"

namespace Bytecode {
    class LessThan final : public Instruction {
    public:
        LessThan() { type = InstructionType::LessThan; };
        [[nodiscard]] std::string toString() const override { return "LessThan"; }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type;
        }
    };
}

#endif//YASI_LESSTHAN_H
