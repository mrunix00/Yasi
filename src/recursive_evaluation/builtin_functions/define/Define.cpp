#include "Define.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/DefinitionsTable.h"
#include <vector>

namespace RecursiveEvaluation {
    SyntaxTreeNode *Define::evaluate(const std::vector<SyntaxTreeNode *> &args) {
        if (args[0]->children.empty()) {
            DefinitionsTable::define(
                    new Variable(args[0]->token->token,
                                 RecursiveEvaluation::evaluate(args[1])));
        } else {
            DefinitionsTable::define(
                    new DefinedFunction(
                            args[0]->token->token,
                            (*args[0]).children,
                            args[1]));
        }
        return new SyntaxTreeNode();
    }

    SyntaxTreeNode *DefinedFunction::evaluate(const std::vector<SyntaxTreeNode *> &args) {
        DefinitionsTable::enterNewScope();
        for (int i = 0; i < args.size(); i++) {
            DefinitionsTable::define(new Variable(
                    arguments[i]->token->token,
                    RecursiveEvaluation::evaluate(args[i])));
        }
        auto result = RecursiveEvaluation::evaluate(definition);
        DefinitionsTable::exitCurrentScope();
        return result;
    }
}// namespace RecursiveEvaluation
