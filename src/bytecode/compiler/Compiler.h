#ifndef YASI_COMPILER_H
#define YASI_COMPILER_H

#include "Segment.h"
#include "bytecode/instructions/Instruction.h"
#include "parser/SyntaxTreeNode.h"
#include <unordered_map>

namespace Bytecode {
    class Compiler {
        std::unordered_map<std::string, size_t> definitions_table;
        size_t counter;

    public:
        std::vector<Segment *> program_segments;
        Compiler() : counter(0) { program_segments.push_back(new Segment({})); };
        void compile(const SyntaxTreeNode &, std::vector<Instruction *> &);
        void compile(const SyntaxTreeNode &);
        void declare(const std::string &);
        size_t find(const std::string &);
    };
}// namespace Bytecode
#endif