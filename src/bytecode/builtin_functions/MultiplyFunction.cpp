#include "MultiplyFunction.h"
#include "bytecode/instructions/Multiply.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Multiply::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        if (args.empty()) throw SyntaxError(
                "Invalid number of arguments for function \"*\", Expected at least 1, got 0",
                0,
                0);
        args[0]->compile(segment, program, instructions);
        if (args.size() == 1) return;
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::Multiply());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Multiply());
        }
    }
}