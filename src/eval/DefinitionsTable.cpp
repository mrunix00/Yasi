#include "DefinitionsTable.h"
#include "builtin_functions/Function.h"
#include "builtin_functions/add/add.h"
#include "builtin_functions/cond/cond.h"
#include "builtin_functions/define/define.h"
#include "builtin_functions/divide/Divide.h"
#include "builtin_functions/equals/equals.h"
#include "builtin_functions/greater_than/greater_than.h"
#include "builtin_functions/less_than/less_than.h"
#include "builtin_functions/multiply/multiply.h"
#include "builtin_functions/print/print.h"
#include "builtin_functions/subtract/subtract.h"
#include <stack>
#include <string>

static std::vector<Function *> scope_stack;
static std::stack<size_t> scopes_sizes;

void DefinitionsTable::initialize() {
    scope_stack = {
            new Add,
            new Subtract,
            new Multiply,
            new Divide,
            new Print,
            new Define,
            new GreaterThan,
            new LessThan,
            new Equals,
            new Cond,
    };
    scopes_sizes.push(scope_stack.size());
}

Function *DefinitionsTable::find(const std::string &name) {
    if (scope_stack.empty()) initialize();

    for (auto i = scope_stack.size(); i > 0; i--) {
        auto func = scope_stack[i - 1];
        if (func->getName() == name)
            return func;
    }

    return nullptr;
}

void DefinitionsTable::define(Function *newFunction) {
    if (scope_stack.empty()) initialize();
    scope_stack.push_back(newFunction);
    scopes_sizes.top()++;
}

void DefinitionsTable::enterNewScope() {
    scopes_sizes.push(0);
}

void DefinitionsTable::exitCurrentScope() {
    auto initial_size = scope_stack.size();
    for (auto i = initial_size; i > initial_size - scopes_sizes.top(); i--) {
        scope_stack.pop_back();
    }
    scopes_sizes.pop();
}
