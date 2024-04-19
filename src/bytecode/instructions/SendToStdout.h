#pragma once
#include "Instruction.h"

namespace Bytecode {
    class SendToStdout final : public Instruction {
    public:
        explicit SendToStdout() {
            type = InstructionType::SendToStdout;
        }
        void execute(Bytecode::VM &vm) override {
            std::cout << vm.program_stack.pop().toString();
        }
        [[nodiscard]] std::string toString() const override { return "SendToStdout"; }
    };
}// namespace Bytecode