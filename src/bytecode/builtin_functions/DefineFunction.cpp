#include "DefineFunction.h"

namespace Bytecode::BuiltinFunctions {
    void Define::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *result) {
        if (args[0]->type == SyntaxTreeNode::TokenNode) {
            const auto reg = program.declare_global(
                    ((TokenNode *) args[0])->getName());
            if (args[1]->type == SyntaxTreeNode::TokenNode &&
                ((TokenNode *) args[1])->token.type != Token::Symbol) {
                program.declare_constant(
                        ((TokenNode *) args[0])->getName(),
                        StackObject(((TokenNode *) args[1])->token));
                return;
            }
            args[1]->compile(result, program, instructions);
            instructions.push_back(new (Instruction){Instruction::StoreGlobal, {.r_param = {reg}}});
        } else if (args[0]->type == SyntaxTreeNode::Expression) {
            auto segment = new Segment({});
            program.declare_function(((Expression *) args[0])->getName(), segment);
            for (auto argument: ((Expression *) args[0])->getArgs())
                segment->declare_variable(((TokenNode *) argument)->getName());
            args[1]->compile(segment, program, segment->instructions);
            segment->instructions.push_back(new (Instruction){Instruction::Return});
        }
    }
}// namespace Bytecode::BuiltinFunctions