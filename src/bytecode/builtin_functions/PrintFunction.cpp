#include "PrintFunction.h"

namespace Bytecode::BuiltinFunctions {
    void Print::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        for (const auto arg: args) {
            arg->compile(segment, program, instructions);
            instructions.push_back(new (Instruction){Instruction::SendToStdout});
        }
        instructions.push_back(new (Instruction){
                Instruction::LoadLiteral,
                {.i_param = {StackObject(std::string("\n"))}},
        });
        instructions.push_back(new (Instruction){Instruction::SendToStdout});
    };
}// namespace Bytecode::BuiltinFunctions