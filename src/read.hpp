#include <exception>
#include <iostream>

extern "C" {
char *linenoise(const char *);
int linenoiseHistoryAdd(char *);
}

class ProgramExit : std::exception {
};

std::string readCommand();
