
#include "AddFunction.h"
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
        if (args.size() == 1) {
            args[0]->compile(segment, program, instructions);
            return;
        }

        if (args[1]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode *) args[1])->getName() == "1") {
            args[0]->compile(segment, program, instructions);
            instructions.push_back(new (Instruction){Instruction::Increment});
            return;
        }

        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode *) args[0])->getName() == "1") {
            args[1]->compile(segment, program, instructions);
            instructions.push_back(new (Instruction){Instruction::Increment});
            return;
        }

        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            args[1]->type == SyntaxTreeNode::TokenNode) {
            if (((TokenNode *) args[0])->token.type == Token::Symbol &&
                ((TokenNode *) args[1])->token.type == Token::Number &&
                segment->find_variable(((TokenNode *) args[0])->getName()) != -1) {
                instructions.push_back(new (Instruction){
                        Instruction::AddRI,
                        {.ri_params = {
                                 segment->find_variable(((TokenNode *) args[0])->getName()),
                                 StackObject(((TokenNode *) args[1])->token)}},
                });
                return;
            }
            if (((TokenNode *) args[0])->token.type == Token::Number &&
                ((TokenNode *) args[1])->token.type == Token::Symbol &&
                segment->find_variable(((TokenNode *) args[1])->getName()) != -1) {
                instructions.push_back(new (Instruction){
                        Instruction::AddRI,
                        {.ri_params = {
                                 segment->find_variable(((TokenNode *) args[1])->getName()),
                                 StackObject(((TokenNode *) args[0])->token)}},
                });
                return;
            }
            if (((TokenNode *) args[0])->token.type == Token::Symbol &&
                ((TokenNode *) args[1])->token.type == Token::Symbol &&
                segment->find_variable(((TokenNode *) args[0])->getName()) != -1 &&
                segment->find_variable(((TokenNode *) args[1])->getName()) != -1) {
                instructions.push_back(new (Instruction){
                        Instruction::AddRR,
                        {.rr_params = {
                                 segment->find_variable(((TokenNode *) args[0])->getName()),
                                 segment->find_variable(((TokenNode *) args[1])->getName()),
                         }},
                });
                return;
            }
        }

        args[0]->compile(segment, program, instructions);
        args[1]->compile(segment, program, instructions);
        instructions.push_back(new (Instruction){Instruction::Add});

        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(segment, program, instructions);
            instructions.push_back(new (Instruction){Instruction::Add});
        }
    }
}// namespace Bytecode::BuiltinFunctions