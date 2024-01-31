#ifndef YASI_FUNCTION_H
#define YASI_FUNCTION_H

#include "bytecode/compiler/Compiler.h"
#include "parser/SyntaxTreeNode.h"
#include <vector>

namespace Bytecode::BuiltinFunctions {
    class Function {
    public:
        virtual void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *) = 0;

    };
}// namespace Bytecode::BuiltinFunctions
#endif//YASI_FUNCTION_H
