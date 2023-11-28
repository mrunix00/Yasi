#include <unordered_map>
#include "eval.h"
#include "../builtin_functions/add/add.h"
#include "../builtin_functions/multiply/multiply.h"
#include "../builtin_functions/subtract/subtract.h"
#include "exceptions/SyntaxError.h"
#include "builtin_functions/divide/Divide.h"

SyntaxTreeNode Evaluate::evaluate(const SyntaxTreeNode &tree) {
    static std::unordered_map<std::string, Function *> builtin = {
            {"+", dynamic_cast<Function *>(new Add())},
            {"-", dynamic_cast<Function *>(new Subtract())},
            {"*", dynamic_cast<Function *>(new Multiply())},
            {"/", dynamic_cast<Function *>(new Divide())}
    };
    if (tree.children.empty()) {
        return SyntaxTreeNode(tree.token);
    }
    if (builtin.find(tree.token.token) != builtin.end()) {
        return builtin.at(tree.token.token)->evaluate(tree.children);
    } else {
        auto errorMessage = "Syntax error: name `"
                            + tree.token.token +
                            "` is not defined";
        throw SyntaxError(errorMessage);
    }
}