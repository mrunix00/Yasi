#include "ReadFunction.h"
#include "bytecode/instructions/ReadFromStdin.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Read::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        if (!args.empty()) {
            throw SyntaxError(
                    "Invalid number of arguments for function \"read\", Expected 0, got " +
                    std::to_string(args.size()));
        }
        instructions.push_back(new ReadFromStdin());
    };
}// namespace Bytecode::BuiltinFunctions