#ifndef YASI_SUBTRACT_FUNCTION_H
#define YASI_SUBTRACT_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/Subtract.h"

namespace Bytecode::BuiltinFunctions {
    class Subtract : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Bytecode::Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Bytecode::Subtract());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Bytecode::Subtract());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
#endif//YASI_SUBTRACT_FUNCTION_H
