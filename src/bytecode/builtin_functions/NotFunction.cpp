#include "NotFunction.h"
#include "bytecode/instructions/Not.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Not::compile(const std::vector<SyntaxTreeNode *> &args,
                      Program &program,
                      std::vector<Instruction *> &instructions,
                      Segment *segment) {
        if (args.size() != 1) {
            throw SyntaxError("Invalid number of arguments for function \"not\", Expected 1, got "
                              + std::to_string(args.size()));
        }
        args[0]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::Not());
    }
}// namespace Bytecode::BuiltinFunctions