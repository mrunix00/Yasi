#include "SyntaxTreeNode.h"
#include "bytecode/builtin_functions/AddFunction.h"
#include "bytecode/builtin_functions/CondFunction.h"
#include "bytecode/builtin_functions/DefineFunction.h"
#include "bytecode/builtin_functions/DivideFunction.h"
#include "bytecode/builtin_functions/EqualsFunction.h"
#include "bytecode/builtin_functions/Function.h"
#include "bytecode/builtin_functions/GreaterThanFunction.h"
#include "bytecode/builtin_functions/IfFunction.h"
#include "bytecode/builtin_functions/LessThanFunction.h"
#include "bytecode/builtin_functions/MultiplyFunction.h"
#include "bytecode/builtin_functions/NotFunction.h"
#include "bytecode/builtin_functions/PrintFunction.h"
#include "bytecode/builtin_functions/SubtractFunction.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLocal.h"

void TokenNode::compile(
        Bytecode::Segment *segment,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    switch (token.type) {
        case Token::Number:
            instructions.push_back(
                    new Bytecode::LoadLiteral(token.asNumber()));
            break;
        case Token::String:
            instructions.push_back(
                    new Bytecode::LoadLiteral(token.asString()));
            break;
        case Token::Symbol:
            if (segment->find_variable(token.token) != -1) {
                instructions.push_back(new Bytecode::LoadLocal(
                        segment->find_variable(token.asString())));
                return;
            }
            if (program.find_global(token.token) != -1) {
                instructions.push_back(new Bytecode::LoadGlobal(
                        program.find_global(token.asString())));
                return;
            }
        default:
            break;
    }
}

void Expression::compile(
        Bytecode::Segment *segment,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    static std::unordered_map<std::string, Bytecode::BuiltinFunctions::Function *> builtin_instructions = {
            {"+", new Bytecode::BuiltinFunctions::Add},
            {"*", new Bytecode::BuiltinFunctions::Multiply},
            {"/", new Bytecode::BuiltinFunctions::Divide},
            {"-", new Bytecode::BuiltinFunctions::Subtract},
            {"=", new Bytecode::BuiltinFunctions::Equals},
            {"<", new Bytecode::BuiltinFunctions::LessThan},
            {">", new Bytecode::BuiltinFunctions::GreaterThan},
            {"define", new Bytecode::BuiltinFunctions::Define},
            {"if", new Bytecode::BuiltinFunctions::If},
            {"cond", new Bytecode::BuiltinFunctions::Cond},
            {"print", new Bytecode::BuiltinFunctions::Print},
            {"not", new Bytecode::BuiltinFunctions::Not},
    };

    if (program.find_function(function.token) != -1) {
        for (const auto &argument: args)
            argument->compile(segment, program, instructions);
        const auto called_segment = program.find_function(function.asString());
        const auto arguments = program.segments[called_segment]->variables_table.size();
        instructions.push_back(new Bytecode::Call(called_segment, arguments));
        return;
    } else if (builtin_instructions.find(function.token) != builtin_instructions.end()) {
        builtin_instructions[function.token]->compile(
                args,
                program,
                instructions,
                segment);
    }
}
