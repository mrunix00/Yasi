#ifndef YASI_GREATER_THAN_FUNCTION_H
#define YASI_GREATER_THAN_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/GreaterThan.h"

namespace Bytecode::BuiltinFunctions {
    class GreaterThan : public Function {
        void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Bytecode::Instruction *> &result) override {
            compiler.compile(*args[0], result);
            compiler.compile(*args[1], result);
            result.push_back(new Bytecode::GreaterThan());
            for (int i = 2; i < args.size(); i++) {
                compiler.compile(*args[i], result);
                result.push_back(new Bytecode::GreaterThan());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions
#endif//YASI_GREATER_THAN_FUNCTION_H
