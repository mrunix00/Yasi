#include "break_lines.h"
#include <stack>

std::vector<std::string> break_lines(const std::string &input) {
    std::vector<std::string> result;
    std::string current_line;
    std::stack<char> brackets_stack;

    for (auto c: input) {
        current_line.push_back(c);
        if (c == '(') {
            brackets_stack.push(c);
        } else if (c == ')') {
            brackets_stack.pop();
            if (brackets_stack.empty()) {
                result.push_back(current_line);
                current_line = "";
            }
        }
    }
    return result;
}