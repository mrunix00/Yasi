#include "LessThanFunction.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/LessThanRI.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void LessThan::compile(
            const std::vector<SyntaxTreeNode *> &args,
            Program &program,
            std::vector<Instruction *> &instructions,
            Segment *segment)  {
        if (args.empty()) {
            throw SyntaxError("Invalid number of arguments for function \"<\", Expected at least 1, got 0");
        }
        if (args.size() == 1) {
            instructions.push_back(new LoadLiteral(new StackObject(true)));
            return;
        }
        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            args[1]->type == SyntaxTreeNode::TokenNode &&
            segment->find_variable(((TokenNode *) args[0])->getName()) != -1) {
            if (((TokenNode *) args[0])->token.type == Token::Symbol &&
                ((TokenNode *) args[1])->token.type == Token::Number) {
                instructions.push_back(
                        new Bytecode::LessThanRI(
                                segment->find_variable(((TokenNode *) args[0])->getName()),
                                ((TokenNode *) args[1])->token.asNumber()));
                return;
            }
        }

        args[0]->compile(segment, program, instructions);
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new Bytecode::LessThan());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new Bytecode::LessThan());
        }
    }
}