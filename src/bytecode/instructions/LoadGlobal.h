#pragma once

#include "Instruction.h"

namespace Bytecode {
    class LoadGlobal final : public Instruction {
        size_t reg;

    public:
        explicit LoadGlobal(const size_t reg) : reg(reg) { type = InstructionType::LoadGlobal; };
        void execute(VM *vm) override {
            vm->stackPush(vm->getGlobal(reg));
        }
        [[nodiscard]] std::string toString() const override {
            return "LoadGlobal $g" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                dynamic_cast<const LoadGlobal *>(&instruction)->reg == reg;
        }
    };
}// namespace Bytecode
