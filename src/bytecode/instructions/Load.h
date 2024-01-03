#ifndef YASI_LOAD_H
#define YASI_LOAD_H

#include "Instruction.h"
#include <cstdio>

namespace Bytecode {
    class Load final : public Instruction {
        size_t reg;

    public:
        explicit Load(size_t reg) : reg(reg) { type = InstructionType::Load; };
        [[nodiscard]] std::string toString() const override {
            return "Load $r" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return getType() == type && ((Load *) &instruction)->reg == reg;
        }
    };
}// namespace Bytecode

#endif
