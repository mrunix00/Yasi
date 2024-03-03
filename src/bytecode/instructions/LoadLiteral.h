#pragma once

#include <sstream>
#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        StackObject *literal;

        explicit LoadLiteral(double value) {
            type = InstructionType::LoadLiteral;
            literal = new StackObject(value);
        };

        explicit LoadLiteral(const std::string &value) {
            type = InstructionType::LoadLiteral;
            literal = new StackObject(value);
        };

        explicit LoadLiteral(StackObject *literal) : literal(literal) {}

        void execute(VM *vm) override {
            switch (literal->type) {
                case ObjectType::Number:
                    vm->program_stack.push(literal->asNumber());
                    break;
                case ObjectType::String:
                    vm->program_stack.push(literal->asString());
                    break;
                case ObjectType::Boolean:
                    vm->program_stack.push(literal->asBoolean());
                    break;
                default:
                    throw std::exception();
            }
        }
        [[nodiscard]] std::string toString() const override {
            std::string value;
            std::stringstream s;
            switch (literal->type) {
                case ObjectType::Number:
                    s << literal->asNumber();
                    value = s.str();
                    break;
                case ObjectType::String:
                    value = std::string(literal->asString());
                    break;
                case ObjectType::Boolean:
                    value = literal->asBoolean()
                                    ? std::string("true")
                                    : std::string("false");
            }
            return "LoadLiteral " + value;
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   *(dynamic_cast<const LoadLiteral *>(&instruction)->literal) == *literal;
        }
    };
}// namespace Bytecode
