#ifndef YASI_SEGMENT_H
#define YASI_SEGMENT_H

#include "bytecode/instructions/Instruction.h"
#include <unordered_map>
#include <utility>
#include <vector>

namespace Bytecode {
    class Segment {
        std::unordered_map<std::string, size_t> variables_table;

    public:
        explicit Segment(const std::vector<Instruction *> &instructions)
            : instructions(instructions) {}

        size_t declare_variable(const std::string &name) {
            return variables_table[name] = variables_table.size();
        }

        size_t find_variable(const std::string &name) {
            if (variables_table.find(name) != variables_table.end()) return variables_table[name];
            return -1;
        }

        inline bool operator==(const Segment &segment) const {
            if (segment.instructions.size() != instructions.size())
                return false;
            for (size_t i = 0; i < instructions.size(); i++) {
                if (!(*instructions[i] == *segment.instructions[i]))
                    return false;
            }
            return true;
        }
        std::vector<Instruction *> instructions;
    };
}// namespace Bytecode

#endif//YASI_SEGMENT_H
