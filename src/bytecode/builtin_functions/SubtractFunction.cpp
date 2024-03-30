#include "SubtractFunction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Subtract.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Subtract::compile(const std::vector<SyntaxTreeNode *> &args,
                           Program &program,
                           std::vector<Instruction *> &instructions,
                           Segment *result) {
        if (args.empty()) {
            throw SyntaxError(
                    "Invalid number of arguments for function \"-\", Expected at least 1, got 0",
                    0,
                    0);
        } else if (args.size() == 1) {
            instructions.push_back(new LoadLiteral((double) 0));
            args[0]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Subtract());
            return;
        }
        args[0]->compile(result, program, instructions);
        args[1]->compile(result, program, instructions);
        instructions.push_back(new Bytecode::Subtract());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Subtract());
        }
    }
}// namespace Bytecode::BuiltinFunctions