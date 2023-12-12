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
#include <unordered_map>

static std::vector<std::unordered_map<std::string, Function *>> scope_stack;

void DefinitionsTable::initialize() {
    std::unordered_map<std::string, Function *> current_scope;
    const std::vector<Function *> builtin_functions = {
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

    for (const auto &function: builtin_functions)
        current_scope[function->getName()] = function;
    scope_stack.push_back(current_scope);
}

Function *DefinitionsTable::find(const std::string &name) {
    if (scope_stack.empty()) initialize();

    for (auto i = scope_stack.size(); i > 0; i--) {
        if (scope_stack[i - 1].find(name) != scope_stack[i - 1].end()) {
            return scope_stack[i - 1].at(name);
        }
    }

    return nullptr;
}

void DefinitionsTable::define(Function *newFunction) {
    if (scope_stack.empty()) initialize();
    scope_stack.back()[newFunction->getName()] = newFunction;
}

void DefinitionsTable::enterNewScope() { scope_stack.emplace_back(); }

void DefinitionsTable::exitCurrentScope() { scope_stack.pop_back(); }
