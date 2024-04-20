#pragma once

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    struct Instruction {
        enum InstructionType : uint8_t {
            Unknown,
            LoadLiteral,
            LoadLocal,
            LoadGlobal,
            Add,
            Subtract,
            Divide,
            Multiply,
            Not,
            Equals,
            GreaterThan,
            LessThan,
            Call,
            CallLambda,
            CondJumpIfNot,
            Jump,
            StoreGlobal,
            SendToStdout,
            ReadFromStdin,
            Or,
            And,
            Return,
            Increment,
            Decrement,
            AddRI,
            SubtractRI,
            LessThanRI,
            DecrementR,
            EqualsRI,
            GreaterThanRI,
            MultiplyRI,
            AddRR,
            StoreLocal,
        } type;
        union params {
            struct RI_Params {
                size_t reg;
                StackObject intermediate;
            } ri_params;
            struct RR_Params {
                size_t reg1;
                size_t reg2;
            } rr_params;
            struct R_Param {
                size_t reg;
            } r_param;
            struct I_param {
                StackObject intermediate;
            } i_param;
            void *none;
        } params{.none = nullptr};
        Instruction() : type(InstructionType::Unknown){};
        virtual ~Instruction() = default;
        virtual void execute(VM &vm) = 0;
        [[nodiscard]] virtual std::string toString() const = 0;
    };
}// namespace Bytecode
