#include "RecursiveEvaluation.h"
#include "DefinitionsTable.h"
#include "builtin_functions/print/Print.h"
#include "exceptions/SyntaxError.h"

namespace RecursiveEvaluation {
    SyntaxTreeNode *evaluate(const SyntaxTreeNode *tree) {
        if (tree == nullptr) return nullptr;
        if (tree->children.empty() && tree->token->type != Token::Symbol) {
            return const_cast<SyntaxTreeNode *>(tree);
        }

        Function *function = DefinitionsTable::find(*tree->token->token);

        if (function == nullptr) {
            auto errorMessage =
                    "name `" + *tree->token->token + "` is not defined";
            throw SyntaxError(errorMessage, tree->token->line, tree->token->column);
        }

        try {
            return function->evaluate(tree->children);
        } catch (const SyntaxError &error) {
            if (error.line == 0 && error.column == 0)
                throw SyntaxError(
                        error.message,
                        tree->token->line,
                        tree->token->column);
            throw;
        }
    }
}