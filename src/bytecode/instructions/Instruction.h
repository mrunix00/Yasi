#pragma once

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    enum class InstructionType {
        Unknown,
        LoadLiteral,
        Load,
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
        LoadGlobal,
    };

    class Instruction {

    public:
        InstructionType type;
        Instruction() : type(InstructionType::Unknown){};
        virtual ~Instruction() = default;
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual void execute(VM *vm) = 0;
        virtual bool operator==(const Instruction &instruction) const = 0;
    };
}// namespace Bytecode
