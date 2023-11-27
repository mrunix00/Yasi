#include <unordered_map>
#include "eval.h"
#include "../builtin_functions/add/add.h"
#include "../builtin_functions/multiply/multiply.h"
#include "../builtin_functions/subtract/subtract.h"
#include "exceptions/SyntaxError.h"

SyntaxTreeNode evaluate(const SyntaxTreeNode &tree) {
    static std::unordered_map<std::string, Function*> built_in  = {
            {"+", dynamic_cast<Function*>(new Add())},
            {"-", dynamic_cast<Function*>(new Subtract())},
            {"*", dynamic_cast<Function*>(new Multiply())}
    };
    if (built_in.find(tree.token.token) != built_in.end()) {
        return built_in.at(tree.token.token)->evaluate(tree.children);
    } else {
        auto errorMessage = "Syntax error: name `"
                            + tree.token.token +
                            "` is not defined";
        throw SyntaxError(errorMessage);
    }
}