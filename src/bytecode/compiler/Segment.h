#ifndef YASI_SEGMENT_H
#define YASI_SEGMENT_H

#include "bytecode/instructions/Instruction.h"
#include <utility>
#include <vector>

namespace Bytecode {
    class Segment {

    public:
        explicit Segment(const std::vector<Instruction *> &instructions)
            : instructions(instructions) {}

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
