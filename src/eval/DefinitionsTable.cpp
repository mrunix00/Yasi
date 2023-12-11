#include "DefinitionsTable.h"
#include "builtin_functions/Function.h"
#include "builtin_functions/add/add.h"
#include "builtin_functions/define/define.h"
#include "builtin_functions/divide/Divide.h"
#include "builtin_functions/greater_than/greater_than.h"
#include "builtin_functions/less_than/less_than.h"
#include "builtin_functions/multiply/multiply.h"
#include "builtin_functions/print/print.h"
#include "builtin_functions/subtract/subtract.h"
#include <stack>
#include <string>
#include <unordered_map>

std::stack<std::unordered_map<std::string, Function *>> DefinitionsTable::scope_stack;

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
    };

    for (const auto &function: builtin_functions)
        current_scope[function->getName()] = function;
    scope_stack.push(current_scope);
}

// This function is very inefficient, I should improve it later
Function *DefinitionsTable::find(const std::string &name) {
    if (scope_stack.empty()) initialize();
    auto temp_stack = scope_stack;

    while (!temp_stack.empty()) {
        if (temp_stack.top().find(name) != temp_stack.top().end()) {
            return temp_stack.top().at(name);
        } else {
            temp_stack.pop();
        }
    }
    return nullptr;
}

void DefinitionsTable::define(Function *newFunction) {
    if (scope_stack.empty()) initialize();
    scope_stack.top()[newFunction->getName()] = newFunction;
}

void DefinitionsTable::enterNewScope() { scope_stack.emplace(); }

void DefinitionsTable::exitCurrentScope() { scope_stack.pop(); }
