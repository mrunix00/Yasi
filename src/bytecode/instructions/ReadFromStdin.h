#pragma once
#include "Instruction.h"

namespace Bytecode {
    class ReadFromStdin final : public Instruction {
    public:
        explicit ReadFromStdin() {
            type = InstructionType::ReadFromStdin;
        }
        void execute(Bytecode::VM &vm) override {
            std::string input;
            std::getline(std::cin, input);
            char *p;
            double number = std::strtod(input.c_str(), &p);
            if (*p)
                vm.program_stack.push(input);
            else
                vm.program_stack.push(number);
        }
        [[nodiscard]] std::string toString() const override { return "ReadFromStdin"; }
    };
}// namespace Bytecode