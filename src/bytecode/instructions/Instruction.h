#pragma once

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    enum class InstructionType {
        Unknown,
        LoadLiteral,
        LoadLocal,
        LoadGlobal,
        Add,
        Subtract,
        Divide,
        Multiply,
        Not,
        Store,
        Equals,
        GreaterThan,
        LessThan,
        Call,
        CondJumpIfNot,
        Jump,
        StoreGlobal,
    };

    class Instruction {
    public:
        InstructionType type;
        uint32_t reg{};
        uint32_t param{};
        StackObject literal{};
        Instruction() : type(InstructionType::Unknown){};
        virtual ~Instruction() = default;
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual void execute(VM *vm) = 0;
        virtual bool operator==(const Instruction &instruction) const = 0;
    };
}// namespace Bytecode
