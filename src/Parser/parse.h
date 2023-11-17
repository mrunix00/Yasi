#ifndef DUMMYLISP_PARSE_H
#define DUMMYLISP_PARSE_H

#include "AbstractSyntaxTree.h"

AbstractSyntaxTree parse(const std::vector<Token> &tokens);

#endif //DUMMYLISP_PARSE_H
