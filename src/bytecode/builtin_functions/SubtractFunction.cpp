#include "SubtractFunction.h"
#include "bytecode/instructions/AddRI.h"
#include "bytecode/instructions/Decrement.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Subtract.h"
#include "bytecode/instructions/SubtractRI.h"
#include "exceptions/SyntaxError.h"

namespace Bytecode::BuiltinFunctions {
    void Subtract::compile(const std::vector<SyntaxTreeNode *> &args,
                           Program &program,
                           std::vector<Instruction *> &instructions,
                           Segment *result) {
        if (args.empty()) {
            throw SyntaxError(
                    "Invalid number of arguments for function \"-\", Expected at least 1, got 0",
                    0,
                    0);
        } else if (args.size() == 1) {
            instructions.push_back(new LoadLiteral((double) 0));
            args[0]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Subtract());
            return;
        }

        if (args[1]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode *) args[1])->getName() == "1") {
            args[0]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Decrement());
            return;
        }

        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode *) args[0])->getName() == "1") {
            args[1]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Decrement());
            return;
        }


        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            args[1]->type == SyntaxTreeNode::TokenNode &&
            result->find_variable(((TokenNode *) args[0])->getName()) != -1) {
            if (((TokenNode *) args[0])->token.type == Token::Symbol &&
                ((TokenNode *) args[1])->token.type == Token::Number) {
                instructions.push_back(
                        new Bytecode::SubtractRI(
                                result->find_variable(((TokenNode *) args[0])->getName()),
                                ((TokenNode *) args[1])->token.asNumber()));
                return;
            }
        }

        args[0]->compile(result, program, instructions);
        args[1]->compile(result, program, instructions);
        instructions.push_back(new Bytecode::Subtract());
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(result, program, instructions);
            instructions.push_back(new Bytecode::Subtract());
        }
    }
}// namespace Bytecode::BuiltinFunctions