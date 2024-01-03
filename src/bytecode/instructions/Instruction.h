#ifndef YASI_INSTRUCTION_H
#define YASI_INSTRUCTION_H

#include <string>
namespace Bytecode {
    enum class InstructionType {
        Unknown,
        LoadLiteral,
        Load,
        Add,
        Subtract,
        Store,
        Equals,
        GreaterThan,
        LessThan,
    };

    class Instruction {
    protected:
        InstructionType type;

    public:
        Instruction() : type(InstructionType::Unknown){};
        [[nodiscard]] InstructionType getType() const { return type; };
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual bool operator==(const Instruction &instruction) const = 0;
    };
}// namespace Bytecode
#endif