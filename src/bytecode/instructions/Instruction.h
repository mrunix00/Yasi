#ifndef YASI_INSTRUCTION_H
#define YASI_INSTRUCTION_H

namespace Bytecode {
    enum class InstructionType {
        LoadLiteral,
        Add,
        Unknown,
    };

    class Instruction {
    protected:
        InstructionType type;

    public:
        Instruction() : type(InstructionType::Unknown){};
        [[nodiscard]] InstructionType getType() const { return type; };
        virtual bool operator==(const Instruction &instruction) const {
            return type == instruction.type;
        }
    };
}// namespace Bytecode
#endif