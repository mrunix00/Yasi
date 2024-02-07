#pragma once
#include <exception>
#include <string>

extern "C" {
char *linenoise(const char *);
int linenoiseHistoryAdd(char *);
}

class ProgramExit final : std::exception {
};

std::string readCommand();
