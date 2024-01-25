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
            if (args[1]->children.empty()) {
                compiler.compile(*args[1], result);
                compiler.declare_variable(*args[0]->token->token);
                result.push_back(new Store(compiler.find(*args[0]->token->token)));
            } else {
                auto segment = new Segment({});
                for (auto argument: args[0]->children)
                    compiler.declare_variable(*argument->token->asString());
                compiler.compile(*args[1], segment->instructions);
                compiler.program_segments.push_back(segment);
                compiler.declare_function(*args[0]->token->asString());
            }
        }
    };
}// namespace Bytecode::BuiltinFunctions

#endif//YASI_DEFINE_FUNCTION_H
