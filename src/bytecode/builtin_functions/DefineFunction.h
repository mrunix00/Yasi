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
            compiler.definitions_table[*args[0]->token->token] = compiler.counter;
            result.push_back(new Store(compiler.counter++));
        }
    };
}

#endif//YASI_DEFINE_FUNCTION_H
