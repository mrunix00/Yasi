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

            compile(*tree.children[0], result);
            compile(*tree.children[1], result);

            if (*tree.token->token == "+") {
                result.push_back(new Add());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new Add());
                }
            } else if (*tree.token->token == "*") {
                result.push_back(new Multiply());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new Multiply());
                }
            } else if (*tree.token->token == "-") {
                result.push_back(new Subtract());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new Subtract());
                }
            } else if (*tree.token->token == "/") {
                result.push_back(new Divide());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new Divide());
                }
            } else if (*tree.token->token == "=") {
                result.push_back(new Equals());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new Equals());
                }
            } else if (*tree.token->token == ">") {
                result.push_back(new GreaterThan());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new GreaterThan());
                }
            } else if (*tree.token->token == "<") {
                result.push_back(new LessThan());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(new LessThan());
                }
            }
            break;
        default:
            break;
    }
}
