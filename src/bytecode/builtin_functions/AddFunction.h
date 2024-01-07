#ifndef YASI_ADD_FUNCTION_H
#define YASI_ADD_FUNCTION_H

#include "./Function.h"
#include "bytecode/instructions/Add.h"

namespace Bytecode::BuiltinFunctions {
    class Add : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Compiler &compiler,
                std::vector<Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Bytecode::Add());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Bytecode::Add());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
#endif//YASI_ADD_FUNCTION_H
