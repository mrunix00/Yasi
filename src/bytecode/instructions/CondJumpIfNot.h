#ifndef YASI_CONDJUMPIFNOT_H
#define YASI_CONDJUMPIFNOT_H

#include "Instruction.h"
namespace Bytecode {
    class CondJumpIfNot final : public Instruction {
        size_t line;

    public:
        explicit CondJumpIfNot(size_t line) : line(line) { type = InstructionType::CondJumpIfNot; }
        void execute(Bytecode::VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "CondJumpIfNot " + std::to_string(line);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type && ((CondJumpIfNot *) &instruction)->line == line;
        }
    };
}// namespace Bytecode

#endif//YASI_CONDJUMPIFNOT_H
