#include "define.h"
#include "eval/DefinitionsTable.h"
#include "eval/eval.h"
#include "parser/SyntaxTreeNode.h"
#include <cassert>
#include <vector>

SyntaxTreeNode Define::evaluate(const std::vector<SyntaxTreeNode> &args) {
    if (args[0].children.empty()) {
        Variable *variable = new Variable(args[0].token.token, args[1]);
        DefinitionsTable::define(variable);
    } else {
        DefinedFunction *function = new DefinedFunction(
                args[0].token.token,
                args[0].children,
                args[1]);
        DefinitionsTable::define(function);
    }
    return {};
}

SyntaxTreeNode DefinedFunction::evaluate(const std::vector<SyntaxTreeNode> &args) {
    assert(args.size() == arguments.size());
    DefinitionsTable::enterNewScope();
    for (int i = 0; i < args.size(); i++) {
        DefinitionsTable::define(new Variable(
                arguments[i].token.token,
                args[i]));
    }
    auto result = Evaluate::evaluate(definition);
    DefinitionsTable::exitCurrentScope();
    return result;
}
