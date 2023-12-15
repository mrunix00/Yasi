#ifndef YASI_PRINTAST_H
#define YASI_PRINTAST_H

#include "parser/SyntaxTreeNode.h"
#include "utils/OutputSource.h"

void print_ast(OutputSource *outputSource, const SyntaxTreeNode &ast);

#endif

