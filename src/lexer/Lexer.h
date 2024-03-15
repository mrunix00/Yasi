#pragma once

#include "Token.h"
#include <sstream>
#include <string>
#include <vector>

std::vector<Token *> tokenize(const std::string &line);
