#ifndef YASI_JUMP_H
#define YASI_JUMP_H

#include "Instruction.h"
namespace Bytecode {
    class Jump final : public Instruction {
        size_t line;

    public:
        explicit Jump(size_t line) : line(line) { type = InstructionType::Jump; }
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Jump " + std::to_string(line);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type && ((Jump *) &instruction)->line == line;
        }
    };
}

#endif//YASI_JUMP_H
