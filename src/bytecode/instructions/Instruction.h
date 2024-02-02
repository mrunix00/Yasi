#ifndef YASI_INSTRUCTION_H
#define YASI_INSTRUCTION_H

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    enum class InstructionType {
        Unknown,
        LoadGlobal,
        LoadLiteral,
        Load,
        Add,
        Subtract,
        Divide,
        Multiply,
        Store,
        StoreGlobal,
        Equals,
        GreaterThan,
        LessThan,
        Call,
        CondJumpIfNot,
        Jump,
    };

    class Instruction {
    public:
        InstructionType type;
        Instruction() : type(InstructionType::Unknown){};
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual void execute(Bytecode::VM *vm) = 0;
        virtual bool operator==(const Instruction &instruction) const = 0;
    };
}// namespace Bytecode
#endif