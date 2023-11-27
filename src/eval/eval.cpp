#include "eval.h"
#include "../builtin_functions/add/add.h"
#include "../builtin_functions/multiply/multiply.h"
#include "../builtin_functions/subtract/subtract.h"
#include "exceptions/SyntaxError.h"

SyntaxTreeNode evaluate(const SyntaxTreeNode &tree) {
    if (tree.token == Token(Token::Symbol, "+")) {
        return Add(tree.children).evaluate();
    } else if (tree.token == Token(Token::Symbol, "*")) {
        return Multiply(tree.children).evaluate();
    } else if (tree.token == Token(Token::Symbol, "-")) {
        return Subtract(tree.children).evaluate();
    }

    auto errorMessage = "Syntax error: name `"
                        + tree.token.token +
                        "` is not defined";
    throw SyntaxError(errorMessage);
}