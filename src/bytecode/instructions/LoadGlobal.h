#ifndef YASI_LOADGLOBAL_H
#define YASI_LOADGLOBAL_H

#include "Instruction.h"

namespace Bytecode {
    class LoadGlobal final : public Instruction {
        size_t reg;

    public:
        explicit LoadGlobal(size_t reg) : reg(reg) { type = InstructionType::LoadGlobal; };
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "LoadGlobal $g" + std::to_string(reg);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type && ((LoadGlobal *) &instruction)->reg == reg;
        }
    };
}// namespace Bytecode

#endif//YASI_LOADGLOBAL_H
