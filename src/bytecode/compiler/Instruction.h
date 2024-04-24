#pragma once

#include "bytecode/vm/VM.h"
#include <string>

namespace Bytecode {
    struct Instruction {
        enum InstructionType : uint8_t {
            Invalid,
            LoadLiteral,
            LoadGlobal,
            LoadLocal,
            Add,
            AddRI,
            AddRR,
            Subtract,
            SubtractRI,
            SubtractRR,
            Multiply,
            MultiplyRI,
            MultiplyRR,
            Divide,
            DivideRI,
            DivideRR,
            Increment,
            Decrement,
            DecrementR,
            Equals,
            EqualsRI,
            LessThan,
            LessThanRI,
            GreaterThan,
            GreaterThanRI,
            Not,
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
            StoreLocal,
        } type = Invalid;
        union {
            struct RI_PARAMS {
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
            struct I_Param {
                StackObject intermediate;
            } i_param;
            void *none;
        } params{.none = nullptr};
    };
}// namespace Bytecode
