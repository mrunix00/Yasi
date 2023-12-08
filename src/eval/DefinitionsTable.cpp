#include "DefinitionsTable.h"
#include "builtin_functions/add/add.h"
#include "builtin_functions/divide/Divide.h"
#include "builtin_functions/multiply/multiply.h"
#include "builtin_functions/print/print.h"
#include "builtin_functions/subtract/subtract.h"
#include <unordered_map>

std::unordered_map<std::string, Function *> *DefinitionsTable::table = nullptr;

void DefinitionsTable::initialize() {
    table = new std::unordered_map<std::string, Function *>;
    const std::vector<Function *> builtin_functions = {
            new Add,
            new Subtract,
            new Multiply,
            new Divide,
            new Print,
    };

    for (const auto &function: builtin_functions) 
        (*table)[function->getName()] = function;
}

Function *DefinitionsTable::find(const std::string &name) {
    if (table == nullptr) initialize();
    if (table->find(name) == table->end()) return nullptr;
    return table->at(name);
}
