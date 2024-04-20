#pragma once

#include "Segment.h"
namespace Bytecode::Optimizer {
    bool is_tail_recursive(const Segment &segment, size_t id);
    void optimize_tail_calls(Segment &segment);
}// namespace Bytecode::Optimizer