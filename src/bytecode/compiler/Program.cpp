#include "Program.h"

namespace Bytecode {
    size_t Bytecode::Program::declare_variable(const std::string &name) {
        return variables_table[name] = variables_table.size();
    }
    size_t Program::declare_function(const std::string &name, Segment *segment) {
        segments.push_back(segment);
        return segments_table[name] = segments_table.size() + 1;
    }
    size_t Program::find_variable(const std::string &name) {
        if (variables_table.find(name) == variables_table.end()) return -1;
        return variables_table[name];
    }
    size_t Program::find_function(const std::string &name) {
        if (segments_table.find(name) == segments_table.end()) return -1;
        return segments_table[name];
    }
}// namespace Bytecode