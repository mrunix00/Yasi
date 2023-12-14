#include "Evaluate.h"
#include "DefinitionsTable.h"
#include "builtin_functions/print/Print.h"
#include "exceptions/SyntaxError.h"

SyntaxTreeNode Evaluate::evaluate(const SyntaxTreeNode &tree) {
    if (tree.children.empty() && tree.token.type != Token::Symbol) {
        return {tree.token};
    }
    Function *function = DefinitionsTable::find(tree.token.token);
    if (function != nullptr) {
        SyntaxTreeNode result;
        try {
            result = function->evaluate(tree.children);
        } catch (const SyntaxError &error) {
            if (error.line == 0 && error.column == 0)
                throw SyntaxError(
                        error.message,
                        tree.token.line,
                        tree.token.column);
            throw;
        }
        return result;
    } else {
        auto errorMessage =
                "name `" + tree.token.token + "` is not defined";
        throw SyntaxError(errorMessage, tree.token.line, tree.token.column);
    }
}
