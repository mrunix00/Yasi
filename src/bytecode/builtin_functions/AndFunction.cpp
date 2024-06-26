#include "AndFunction.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void And::compile(const std::vector<SyntaxTreeNode *> &args,
                      Program &program,
                      std::vector<Instruction *> &instructions,
                      Segment *segment) {
        if (args.empty()) throw SyntaxError(
                "Invalid number of arguments for function \"and\", Expected at least 1, got 0");
        args[0]->compile(segment, program, instructions);
        if (args.size() == 1) return;
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new (Instruction){Instruction::And});
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new (Instruction){Instruction::And});
        }
    }
}// namespace Bytecode::BuiltinFunctions