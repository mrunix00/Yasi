#pragma once

#include "Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class AddRR final : public Instruction {
    public:
        AddRR(size_t reg1, size_t reg2) {
            type = InstructionType::AddRR;
            params.rr_params = {reg1, reg2};
        }
        void execute(Bytecode::VM &vm) override {
            const auto object1 = vm.call_stack.getLocal(params.rr_params.reg1);
            const auto object2 = vm.call_stack.getLocal(params.rr_params.reg2);
            if (object1.type != ObjectType::Number ||
                object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
            }
            vm.program_stack.push(object1.asNumber() + object2.asNumber());
        }
        [[nodiscard]] std::string toString() const override {
            return "AddRR $r" + std::to_string(params.rr_params.reg1) +
                   ", $r" + std::to_string(params.rr_params.reg2);
        }
    };
}// namespace Bytecode