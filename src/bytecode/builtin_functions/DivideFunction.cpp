
#include "DivideFunction.h"
#include "bytecode/instructions/Divide.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Divide::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        if (args.empty())
            throw SyntaxError(
                    "Invalid number of arguments for function \"/\", Expected at least 1, got 0",
                    0,
                    0);
        if (args.size() == 1) {
            instructions.push_back(new LoadLiteral((double) 1));
            args[0]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Divide());
            return;
        }
        args[0]->compile(segment, program, instructions);
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::Divide());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Divide());
        }
    }
}// namespace Bytecode::BuiltinFunctions