#pragma once

#include "Instruction.h"
namespace Bytecode {
    class Call final : public Instruction {
        size_t segment;
        size_t args;

    public:
        explicit Call(const size_t segment, const size_t args)
            : segment(segment), args(args) { type = InstructionType::Call; }
        void execute(VM *vm) override {
            vm->newStackFrame(segment);
            for (int i = 0; i < args; i++)
                vm->setLocal(i, vm->stackPop());
        }
        [[nodiscard]] std::string toString() const override {
            return "Call :" + std::to_string(segment);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const Call *>(&instruction)->segment == segment;
        }
    };
}// namespace Bytecode
