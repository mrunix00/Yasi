#include "Program.h"

namespace Bytecode {
    size_t Program::declare_global(const std::string &name) {
        return globals_table[name] = globals_table.size();
    }
    size_t Program::declare_function(const std::string &name, Segment *segment) {
        segments.push_back(segment);
        return segments_table[name] = segments.size() - 1;
    }
    size_t Program::declare_lambda(Segment *segment) {
        segments.push_back(segment);
        return segments.size() - 1;
    }
    size_t Program::find_function(const std::string &name) {
        if (segments_table.find(name) == segments_table.end()) return -1;
        return segments_table[name];
    }
    size_t Program::find_global(const std::string &name) {
        if (globals_table.find(name) != globals_table.end())
            return globals_table[name];
        return -1;
    }
    void Program::declare_constant(const std::string &name, StackObject object) {
        constants_table[name] = object;
    }
    StackObject *Program::find_constant(const std::string &name) {
        if (constants_table.find(name) == constants_table.end()) return nullptr;
        return &constants_table[name];
    }
}// namespace Bytecode