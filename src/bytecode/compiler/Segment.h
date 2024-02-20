#pragma once

#include "bytecode/instructions/Instruction.h"
#include "bytecode/objects/LocalRegister.h"
#include <unordered_map>
#include <vector>

namespace Bytecode {
    class Segment {
    public:
        std::vector<Instruction *> instructions;
        std::unordered_map<std::string, size_t> variables_table;

        explicit Segment(const std::vector<Instruction *> &instructions)
            : instructions(instructions) {}
        ~Segment() {
            for (auto instruction: instructions)
                delete instruction;
        }

        size_t declare_variable(const std::string &name) {
            return variables_table[name] = variables_table.size();
        }

        LocalRegister* find_variable(const std::string &name) {
            if (variables_table.find(name) != variables_table.end()) return new LocalRegister(variables_table[name]);
            return nullptr;
        }

        bool operator==(const Segment &segment) const {
            if (segment.instructions.size() != instructions.size())
                return false;
            for (size_t i = 0; i < instructions.size(); i++) {
                if (!(*instructions[i] == *segment.instructions[i]))
                    return false;
            }
            return true;
        }
    };
}// namespace Bytecode
