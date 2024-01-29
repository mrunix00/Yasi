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
                const auto reg = compiler.program.declare_variable(*args[0]->token->token);
                result.push_back(new Store(reg));
            } else {
                auto segment = new Segment({});
                compiler.program.declare_function(*args[0]->token->asString(), segment);
                for (auto argument: args[0]->children)
                    compiler.program.declare_variable(*argument->token->asString());
                compiler.compile(*args[1], segment->instructions);

            }
        }
    };
}// namespace Bytecode::BuiltinFunctions

#endif//YASI_DEFINE_FUNCTION_H
