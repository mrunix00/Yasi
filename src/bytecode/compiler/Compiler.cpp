#include "Compiler.h"
#include "bytecode/builtin_functions/AddFunction.h"
#include "bytecode/builtin_functions/DefineFunction.h"
#include "bytecode/builtin_functions/DivideFunction.h"
#include "bytecode/builtin_functions/EqualsFunction.h"
#include "bytecode/builtin_functions/Function.h"
#include "bytecode/builtin_functions/GreaterThanFunction.h"
#include "bytecode/builtin_functions/LessThanFunction.h"
#include "bytecode/builtin_functions/MultiplyFunction.h"
#include "bytecode/builtin_functions/SubtractFunction.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"

void Bytecode::Compiler::compile(
        const SyntaxTreeNode &tree,
        std::vector<Instruction *> &result) {
    std::unordered_map<std::string, BuiltinFunctions::Function *> builtin_instructions = {
            {"+", new BuiltinFunctions::Add},
            {"*", new BuiltinFunctions::Multiply},
            {"/", new BuiltinFunctions::Divide},
            {"-", new BuiltinFunctions::Subtract},
            {"=", new BuiltinFunctions::Equals},
            {"<", new BuiltinFunctions::LessThan},
            {">", new BuiltinFunctions::GreaterThan},
            {"define", new BuiltinFunctions::Define},
    };

    switch (tree.token->type) {
        case Token::Integer:
            result.push_back(new LoadLiteral(tree.token->asInteger()));
            break;
        case Token::Symbol:
            if (tree.children.empty()) {
                if (definitions_table.find(*tree.token->token) != definitions_table.end()) {
                    result.push_back(new Load(definitions_table[*tree.token->token]));
                    return;
                }
            } else {
                if (segments_table.find(*tree.token->asString()) != segments_table.end()) {
                    for (const auto &argument: tree.children)
                        compile(*argument, result);
                    result.push_back(new Call(segments_table[*tree.token->asString()]));
                    return;
                }
            }


            if (builtin_instructions.find(*tree.token->token) != builtin_instructions.end()) {
                builtin_instructions[*tree.token->token]->compile(
                        tree.children,
                        *this,
                        result);
            }
            break;
        default:
            break;
    }
}

void Bytecode::Compiler::compile(const SyntaxTreeNode &tree) {
    compile(tree, program_segments[0]->instructions);
}

void Bytecode::Compiler::declare_variable(const std::string &name) {
    definitions_table[name] = definitions_table.size();
}

size_t Bytecode::Compiler::find(const std::string &name) {
    return definitions_table[name];
}

void Bytecode::Compiler::declare_function(const std::string &name) {
    segments_table[name] = segments_table.size() + 1;
}
