#ifndef YASI_SUBTRACT_H
#define YASI_SUBTRACT_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Subtract final : public Instruction, public Compilable {
    public:
        Subtract() { type = InstructionType::Subtract; };
        [[nodiscard]] std::string toString() const override { return "Subtract"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Subtract());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Subtract());
            }
        }
    };
}// namespace Bytecode

#endif//YASI_SUBTRACT_H
