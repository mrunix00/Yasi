
#include "AddFunction.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Increment.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Add::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment) {
        if (args.empty())
            throw SyntaxError(
                "Invalid number of arguments for function \"+\", Expected at least 1, got 0",
                0,
                0);
        if (args[1]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode*) args[1])->getName() == "1") {
            args[0]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Increment());
            return;
        }

        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode*) args[0])->getName() == "1") {
            args[1]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Increment());
            return;
        }

        args[0]->compile(segment, program, instructions);
        if (args.size() == 1) return;
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::Add());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::Add());
        }
    }
}// namespace Bytecode