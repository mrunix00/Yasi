#pragma once
#include "builtin_functions/Function.h"

namespace RecursiveEvaluation {
    class DefinitionsTable {
    protected:
        static void initialize();

    public:
        static Function *find(const std::string &name);
        static void define(Function *);
        static void enterNewScope();
        static void exitCurrentScope();
    };
}
