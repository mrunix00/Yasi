#include "Instruction.h"

namespace Bytecode {
    class Increment final : public Instruction {
    public:
        Increment() { type = InstructionType::Increment; };
        void execute(Bytecode::VM &vm) override {
            vm.program_stack.push(vm.program_stack.pop().asNumber() + 1);
        }
        [[nodiscard]] std::string toString() const override { return "Increment"; }
    };
}// namespace Bytecode