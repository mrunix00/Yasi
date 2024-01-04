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
        Divide,
        Multiply,
        Store,
        Equals,
        GreaterThan,
        LessThan,
    };

    class Instruction {
    public:
        InstructionType type;
        Instruction() : type(InstructionType::Unknown){};
        [[nodiscard]] virtual std::string toString() const = 0;
        virtual bool operator==(const Instruction &instruction) const = 0;
    };
}// namespace Bytecode
#endif