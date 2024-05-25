#pragma once

#include "Program.h"
#include "Segment.h"

namespace Bytecode::Optimizer {
    bool is_tail_recursive(const Segment &segment, size_t id);
    bool is_inlineable(const Segment &segment, size_t id);
    void optimize_tail_calls(Segment &segment);
    void inline_function(Segment &segment, Segment &to_inline, size_t id);
}// namespace Bytecode::Optimizer
