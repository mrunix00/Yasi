#include "DefineFunction.h"
#include "bytecode/instructions/Return.h"
#include "bytecode/instructions/StoreGlobal.h"

namespace Bytecode::BuiltinFunctions {
    void Define::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *result) {
        if (args[0]->type == SyntaxTreeNode::TokenNode) {
            const auto reg = program.declare_global(
                    ((TokenNode *) args[0])->getName());
            args[1]->compile(result, program, instructions);
            instructions.push_back(new StoreGlobal(reg));
        } else if (args[0]->type == SyntaxTreeNode::Expression) {
            auto segment = new Segment({});
            program.declare_function(((Expression *) args[0])->getName(), segment);
            for (auto argument: ((Expression *) args[0])->getArgs())
                segment->declare_variable(((TokenNode *) argument)->getName());
            args[1]->compile(segment, program, segment->instructions);
            segment->instructions.push_back(new Bytecode::Return());
        }
    }
}// namespace Bytecode::BuiltinFunctions