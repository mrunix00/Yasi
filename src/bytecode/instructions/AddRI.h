#pragma once

#include "Instruction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode {
    class AddRI final : public Instruction {
    public:
        AddRI(size_t rg, double number) {
            type = InstructionType::AddRI;
            params = {rg, StackObject(number)};
        }
        void execute(Bytecode::VM &vm) override {
            const auto object1 = params.ri_params.intermediate;
            const auto object2 = vm.call_stack.getLocal(params.ri_params.reg);
            if (object2.type != ObjectType::Number) {
                throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
            }
            vm.program_stack.push(object1.data.number + object2.data.number);
        }
        [[nodiscard]] std::string toString() const override {
            return "AddRI $r" + std::to_string(params.ri_params.reg) +
                   ", " + params.ri_params.intermediate.toString();
        }
    };
}// namespace Bytecode