#ifndef YASI_MULTIPLY_FUNCTION_H
#define YASI_MULTIPLY_FUNCTION_H

#include "Function.h"
#include "bytecode/instructions/Multiply.h"

namespace Bytecode::BuiltinFunctions {
    class Multiply : public Function {
         void compile(
                const std::vector<SyntaxTreeNode *> &args,
                Bytecode::Compiler &compiler,
                std::vector<Instruction *> &instructions,
                Segment *result) override {
             compiler.compile(*args[0], result, instructions);
             compiler.compile(*args[1], result, instructions);
             instructions.push_back(new Bytecode::Multiply());
             for (int i = 2; i < args.size(); i++) {
                 compiler.compile(*args[i], result, instructions);
                 instructions.push_back(new Bytecode::Multiply());
             }
         }
    };
}

#endif//YASI_MULTIPLY_FUNCTION_H
