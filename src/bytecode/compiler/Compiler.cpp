#include "Compiler.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Subtract.h"

void Bytecode::Compiler::compile(
        const SyntaxTreeNode &tree,
        std::vector<Instruction> &result) {
    switch (tree.token->type) {
        case Token::Integer:
            result.push_back(LoadLiteral(tree.token->asInteger()));
            break;
        case Token::Symbol:
            compile(*tree.children[0], result);
            compile(*tree.children[1], result);
            if (*tree.token->token == "+") {
                result.push_back(Add());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(Add());
                }
            } else if (*tree.token->token == "-") {
                result.push_back(Subtract());
                for (int i = 2; i < tree.children.size(); i++) {
                    compile(*tree.children[i], result);
                    result.push_back(Subtract());
                }
            }
            break;
        default:
            break;
    }
}
