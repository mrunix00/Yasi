#pragma once

#include "Instruction.h"

namespace Bytecode {
    class CallLambda final : public Instruction {
    public:
        explicit CallLambda(const size_t args) {
            params.r_param = {args};
            type = InstructionType::CallLambda;
        }
        void execute(Bytecode::VM &vm) override {
            const auto lambda = vm.program_stack.pop();
            vm.call_stack.newStackFrame(
                    lambda.asLambda(),
                    params.r_param.reg,
                    &vm.program_stack);
        }
        [[nodiscard]] std::string toString() const override {
            return "CallLambda " + std::to_string(params.r_param.reg);
        }
    };
}// namespace Bytecode