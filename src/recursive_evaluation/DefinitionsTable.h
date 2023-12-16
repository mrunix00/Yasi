#include "builtin_functions/Function.h"
#include <stack>
#include <unordered_map>

class DefinitionsTable {
protected:
    static void initialize();

public:
    static Function *find(const std::string &name);
    static void define(Function *);
    static void enterNewScope();
    static void exitCurrentScope();
};
