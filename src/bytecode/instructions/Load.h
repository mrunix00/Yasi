#pragma once

#include "Instruction.h"
#include "bytecode/objects/LocalRegister.h"
#include "bytecode/objects/Register.h"

namespace Bytecode {
    class Load final : public Instruction {
        Register *reg;

    public:
        explicit Load(Register *reg) : reg(reg) {
            type = InstructionType::Load;
        }

        void execute(VM *vm) override {
            const auto literal = reg->get(vm);
            const auto number = literal.asNumber();
            vm->program_stack.push((ObjectType) literal.type,
                                   (uint8_t *) &number,
                                   8);
        }

        [[nodiscard]] std::string toString() const override {
            return "Load " + reg->toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   *(dynamic_cast<const Load *>(&instruction)->reg) == *reg;
        }
    };
}// namespace Bytecode
