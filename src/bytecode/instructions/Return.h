#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Return final : public Instruction {
    public:
        Return() { type = InstructionType::Return; }
        void execute(Bytecode::VM &vm) override {
            vm.call_stack.popStackFrame();
        }
        [[nodiscard]] std::string toString() const override { return "Return"; }
    };
}// namespace Bytecode