#pragma once
#include "Instruction.h"
#include "bytecode/objects/BooleanLiteral.h"
namespace Bytecode {
    class CondJumpIfNot final : public Instruction {
        size_t line;

    public:
        explicit CondJumpIfNot(const size_t line) : line(line) { type = InstructionType::CondJumpIfNot; }
        void execute(VM *vm) override {
            const auto cond = vm->stackPop();
            if (!((BooleanLiteral *) cond)->asBoolean())
                vm->jump(line);
            delete cond;
        }
        [[nodiscard]] std::string toString() const override {
            return "CondJumpIfNot " + std::to_string(line);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const CondJumpIfNot *>(&instruction)->line == line;
        }
    };
}// namespace Bytecode
