#include "SubtractFunction.h"
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
            instructions.push_back(new (Instruction){
                    Instruction::LoadLiteral,
                    {.i_param = {StackObject((double) 0)}},
            });
            args[0]->compile(result, program, instructions);
            instructions.push_back(new (Instruction){Instruction::Subtract});
            return;
        }

        if (args[0]->type == SyntaxTreeNode::TokenNode &&
            args[1]->type == SyntaxTreeNode::TokenNode &&
            ((TokenNode *) args[1])->token.type == Token::Number) {
            if (((TokenNode *) args[0])->token.type == Token::Symbol) {
                instructions.push_back(new (Instruction){
                        Instruction::SubtractRI,
                        {.ri_params = {
                                 result->find_variable(((TokenNode *) args[0])->getName()),
                                 StackObject(((TokenNode *) args[1])->token)}},
                });
                return;
            } else if (((TokenNode *) args[1])->getName() == "1"){
                args[0]->compile(result, program, instructions);
                instructions.push_back(new (Instruction){Instruction::Decrement});
                return;
            }
        }

        args[0]->compile(result, program, instructions);
        args[1]->compile(result, program, instructions);
        instructions.push_back(new (Instruction){Instruction::Subtract});
        for (int i = 2; i < args.size(); i++) {
            args[i]->compile(result, program, instructions);
            instructions.push_back(new (Instruction){Instruction::Subtract});
        }
    }
}// namespace Bytecode::BuiltinFunctions