#ifndef YASI_PRINTTOKENS_H
#define YASI_PRINTTOKENS_H

#include "OutputSource.h"
#include "lexer/Lexer.h"
#include <vector>

void printTokens(OutputSource *outputSource,
                 const std::vector<Token *> &tokens);

#endif
