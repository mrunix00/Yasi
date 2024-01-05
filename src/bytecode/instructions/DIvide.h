#ifndef YASI_DIVIDE_H
#define YASI_DIVIDE_H

#include "../compiler/Compiler.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"

namespace Bytecode {
    class Divide final : public Instruction, public Compilable {
    public:
        Divide() { type = InstructionType::Divide; };
        [[nodiscard]] std::string toString() const override { return "Divide"; }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type;
        }
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Divide());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Divide());
            }
        }
    };
}// namespace Bytecode

#endif//YASI_DIVIDE_H
