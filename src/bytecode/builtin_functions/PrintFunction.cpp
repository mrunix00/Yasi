#include "PrintFunction.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/SendToStdout.h"

namespace Bytecode::BuiltinFunctions {
    void Print::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        for (const auto arg: args) {
            arg->compile(segment, program, instructions);
            instructions.push_back(new SendToStdout());
        }
        instructions.push_back(new LoadLiteral("\n"));
        instructions.push_back(new SendToStdout());
    };
}// namespace Bytecode::BuiltinFunctions