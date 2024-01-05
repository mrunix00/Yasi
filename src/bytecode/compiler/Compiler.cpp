#include "Compiler.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/DIvide.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/instructions/Subtract.h"

void Bytecode::Compiler::compile(
        const SyntaxTreeNode &tree,
        std::vector<Instruction *> &result) {
    std::unordered_map<std::string, Compilable *> builtin_instructions = {
            {"+", new Add},
            {"*", new Multiply},
            {"/", new Divide},
            {"-", new Subtract},
            {"=", new Equals},
            {"<", new LessThan},
            {">", new GreaterThan},
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
            if (*tree.token->token == "define") {
                compile(*tree.children[1], result);
                definitions_table[*tree.children[0]->token->token] = counter;
                result.push_back(new Store(counter++));
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
