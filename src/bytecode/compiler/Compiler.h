#ifndef YASI_COMPILER_H
#define YASI_COMPILER_H

#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"
#include <unordered_map>

namespace Bytecode {
    class Compiler {
        std::unordered_map<std::string, size_t> definitions_table;
        size_t counter;

    public:
        Compiler() : counter(0){};
        void compile(const SyntaxTreeNode &, std::vector<Instruction *> &);
    };

    class Compilable {
    public:
        virtual void compile(const std::vector<SyntaxTreeNode *> &args,
                     Compiler &compiler,
                     std::vector<Instruction *> &result) = 0;
    };
}// namespace Bytecode
#endif