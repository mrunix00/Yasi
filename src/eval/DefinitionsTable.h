#include "builtin_functions/Function.h"
#include <unordered_map>

class DefinitionsTable {
protected:
    static std::unordered_map<std::string, Function *> *table;
    static void initialize();

public:
    static Function *find(const std::string &name);
};
