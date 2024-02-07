#pragma once

#include "Instruction.h"

namespace Bytecode {
    class StoreGlobal final : public Instruction {
        size_t reg;

    public:
        explicit StoreGlobal(const size_t rg) {
            reg = rg;
            type = InstructionType::StoreGlobal;
        }
        void execute(Bytecode::VM *vm) override {
            auto object = vm->stackPop();
            vm->setGlobal(reg, object);
        }
        [[nodiscard]] std::string toString() const override {
            return "StoreGlobal $g" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const StoreGlobal *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
