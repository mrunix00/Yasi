#include "eval.h"
#include "../builtin_functions/add/add.h"
#include "../builtin_functions/multiply/multiply.h"
#include "../builtin_functions/subtract/subtract.h"
#include "builtin_functions/divide/Divide.h"
#include "builtin_functions/print/print.h"
#include "exceptions/SyntaxError.h"
#include <unordered_map>

SyntaxTreeNode Evaluate::evaluate(const SyntaxTreeNode &tree) {
    static std::unordered_map<std::string, Function *> builtin = {
            {"+", (Function *) (new Add())},
            {"-", (Function *) (new Subtract())},
            {"*", (Function *) (new Multiply())},
            {"/", (Function *) (new Divide())},
            {"print", (Function *) (new Print())},
    };
    if (tree.children.empty()) {
        return SyntaxTreeNode(tree.token);
    }
    if (builtin.find(tree.token.token) != builtin.end()) {
        return builtin.at(tree.token.token)->evaluate(tree.children);
    } else {
        auto errorMessage =
                "name `" + tree.token.token + "` is not defined";
        throw SyntaxError(errorMessage, tree.token.line, tree.token.column);
    }
}
