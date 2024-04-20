#pragma once

#include "Segment.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace Bytecode {
    class Program {
        std::unordered_map<std::string, size_t> globals_table;
        std::unordered_map<std::string, size_t> segments_table;
        std::unordered_map<std::string, StackObject> constants_table;

    public:
        std::vector<Segment *> segments;

        Program() : segments({new Segment({})}){};
        ~Program() {
            for (const auto segment: segments)
                delete segment;
        }
        explicit Program(const std::vector<Segment *> &segments) : segments(segments){};

        size_t declare_global(const std::string &);
        size_t declare_function(const std::string &, Segment *);
        size_t declare_lambda(Segment *);
        void declare_constant(const std::string &, StackObject);
        size_t find_global(const std::string &);
        size_t find_function(const std::string &);
        StackObject *find_constant(const std::string &);
    };
}// namespace Bytecode
