#include <exception>
#include <string>

extern "C" {
char *linenoise(const char *);
int linenoiseHistoryAdd(char *);
}

class ProgramExit : std::exception {
};

std::string readCommand();
