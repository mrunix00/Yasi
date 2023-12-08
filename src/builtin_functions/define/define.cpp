#include "define.h"
#include "eval/DefinitionsTable.h"
#include <vector>

SyntaxTreeNode Define::evaluate(const std::vector<SyntaxTreeNode> &args) {
    Variable *variable = new Variable(args[0].token.token, args[1]);
    DefinitionsTable::define(variable);
    return {};
}
