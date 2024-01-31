#ifndef YASI_STOREGLOBAL_H
#define YASI_STOREGLOBAL_H

#include "Instruction.h"

namespace Bytecode {
    class StoreGlobal final : public Instruction {
        size_t reg;

    public:
        explicit StoreGlobal(size_t rg) {
            reg = rg;
            type = InstructionType::StoreGlobal;
        }
        [[nodiscard]] std::string toString() const override {
            return "StoreGlobal $g" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type && ((StoreGlobal *) &instruction)->reg == reg;
        }
    };
}// namespace Bytecode

#endif//YASI_STOREGLOBAL_H
