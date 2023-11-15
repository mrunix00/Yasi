#include "read.hpp"
#include <string>

std::string readCommand() {
    char *input;
    if ((input = linenoise(">>> ")) == nullptr) {
        throw ProgramExit();
    }
    linenoiseHistoryAdd(input);
    return input;
}
