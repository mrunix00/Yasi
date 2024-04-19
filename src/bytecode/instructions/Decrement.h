#include "Instruction.h"

namespace Bytecode {
    class Decrement final : public Instruction {
    public:
        Decrement() { type = InstructionType::Decrement; };
        void execute(Bytecode::VM &vm) override {
            vm.program_stack.push(vm.program_stack.pop().asNumber() - 1);
        }
        [[nodiscard]] std::string toString() const override { return "Decrement"; }
    };
}// namespace Bytecode