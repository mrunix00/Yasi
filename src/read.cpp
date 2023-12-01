#include "read.hpp"
#include <stack>
#include <string>

std::string readLine(bool displayLinePointer) {
    char *input;
    if ((input = linenoise(displayLinePointer ? ">>> " : "")) == nullptr) {
        throw ProgramExit();
    }
    linenoiseHistoryAdd(input);
    return input;
}

bool checkParenthesis(std::string input) {
    std::stack<char> parenthesis_stack;
    for (auto c : input) {
        if (c == '(') parenthesis_stack.push(c);
        else if (c == ')') parenthesis_stack.pop();
    }
    return parenthesis_stack.size() == 0;
}

std::string readCommand() {
    auto command = readLine(true);
    while (!checkParenthesis(command)) {
        command = command + readLine(false);
    }
    return command;
}

