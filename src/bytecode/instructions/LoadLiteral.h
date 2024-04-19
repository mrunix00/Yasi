#pragma once

#include "bytecode/instructions/Instruction.h"
#include <sstream>

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        explicit LoadLiteral(const double value) {
            type = Instruction::LoadLiteral;
            params.i_param = {StackObject(value)};
        };

        explicit LoadLiteral(const std::string &value) {
            type = InstructionType::LoadLiteral;
            params.i_param = {StackObject(value)};
        };

        explicit LoadLiteral(const StackObject *literal) {
            params.i_param = {*literal};
            type = InstructionType::LoadLiteral;
        }

        [[nodiscard]] std::string toString() const override {
            if (params.i_param.intermediate.type == ObjectType::String) {
                std::string str = params.i_param.intermediate.toString();
                if (str == "\n") str = "\\n";
                return "LoadLiteral " + std::string("\"") + str + std::string("\"");
            }
            return "LoadLiteral " + params.i_param.intermediate.toString();
        }
    };
}// namespace Bytecode
