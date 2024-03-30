#include "GreaterThanFunction.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void GreaterThan::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        if (args.empty()) {
            throw SyntaxError("Invalid number of arguments for function \">\", Expected at least 1, got 0");
        }
        if (args.size() == 1) {
            instructions.push_back(new LoadLiteral(new StackObject(true)));
            return;
        }
        args[0]->compile(segment, program, instructions);
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::GreaterThan());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::GreaterThan());
        }
    }
}// namespace Bytecode::BuiltinFunctions