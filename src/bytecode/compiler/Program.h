#pragma once

#include "Segment.h"
#include "bytecode/objects/GlobalRegister.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace Bytecode {
    class Program {
        std::unordered_map<std::string, size_t> globals_table;
        std::unordered_map<std::string, size_t> segments_table;

    public:
        std::vector<Segment *> segments;

        Program() : segments({new Segment({})}){};
        ~Program() {
            for (const auto segment: segments)
                delete segment;
        }
        explicit Program(const std::vector<Segment *> &segments) : segments(segments){};

        GlobalRegister *declare_global(const std::string &);
        size_t declare_function(const std::string &, Segment *);
        GlobalRegister *find_global(const std::string &);
        size_t find_function(const std::string &);

        bool operator==(const Program &program) const;
    };
}// namespace Bytecode
