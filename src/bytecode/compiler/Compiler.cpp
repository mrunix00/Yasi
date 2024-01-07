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
            if (definitions_table.find(*tree.token->token) != definitions_table.end()) {
                result.push_back(new Load(definitions_table[*tree.token->token]));
                return;
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
