#pragma once

#include "Instruction.h"

namespace Bytecode {
    class Not final : public Instruction {
    public:
        Not() { type = InstructionType::Not; }
        void execute(Bytecode::VM &vm) override {
            const auto object = vm.program_stack.pop();
            if (object.type != ObjectType::Boolean)
                vm.program_stack.push(false);
            else
                vm.program_stack.push(!object.asBoolean());
        }
        [[nodiscard]] std::string toString() const override { return "Not"; }
    };
}// namespace Bytecode