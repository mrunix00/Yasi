#ifndef YASI_LOADLITERAL_H
#define YASI_LOADLITERAL_H

#include "bytecode/instructions/Instruction.h"

namespace Bytecode {
    class LoadLiteral final : public Instruction {
    public:
        explicit LoadLiteral(int integer) {
            type = InstructionType::LoadLiteral;
            value = integer;
        };
        void execute(Bytecode::VM *vm) override {
            vm->Push(new StackObject(new Literal(value)));
        }
        [[nodiscard]] std::string toString() const override {
            return "LoadLiteral d" + std::to_string(value);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type && ((LoadLiteral *) &instruction)->value == value;
        }
        int value;
    };
}// namespace Bytecode
#endif