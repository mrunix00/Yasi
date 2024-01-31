#ifndef YASI_PROGRAM_H
#define YASI_PROGRAM_H

#include "Segment.h"
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
        explicit Program(const std::vector<Segment *> &segments) : segments(segments) {};

        size_t declare_global(const std::string &);
        size_t declare_function(const std::string &, Segment *);
        size_t find_global(const std::string &);
        size_t find_function(const std::string &);

        inline bool operator==(const Program &program) {
            if (segments.size() != program.segments.size())
                return false;
            for (size_t i = 0; i < segments.size(); i++)
                if (!(*program.segments[i] == *segments[i]))
                    return false;
            return true;
        }
    };
}// namespace Bytecode

#endif//YASI_PROGRAM_H
