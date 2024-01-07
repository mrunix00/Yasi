#ifndef YASI_DEFINE_FUNCTION_H
#define YASI_DEFINE_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/Store.h"

namespace Bytecode::BuiltinFunctions {
    class Define : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Bytecode::Instruction *> &result) override {
            compiler.compile(*args[1], result);
            compiler.declare(*args[0]->token->token);
            result.push_back(new Store(compiler.find(*args[0]->token->token)));
        }
    };
}

#endif//YASI_DEFINE_FUNCTION_H
