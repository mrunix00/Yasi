#pragma once

#include "Instruction.h"
#include "bytecode/objects/LocalRegister.h"
#include "bytecode/objects/Register.h"
#include <string>

namespace Bytecode {
    class Store final : public Instruction {
        Register *reg;

    public:
        explicit Store(Register *reg) : reg(reg) {
            type = InstructionType::Store;
        }

        void execute(Bytecode::VM *vm) override {
            reg->store(vm);
        }
        [[nodiscard]] std::string toString() const override {
            return "Store " + reg->toString();
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   *(dynamic_cast<const Store *>(&instruction)->reg) == *reg;
        }
    };
}// namespace Bytecode
