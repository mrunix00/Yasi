#include "Optimizer.h"

bool Bytecode::Optimizer::is_tail_recursive(const Bytecode::Segment &segment, size_t id) {
    const auto &instructions = segment.instructions;
    return instructions.back()->type == Instruction::Return &&
           instructions[instructions.size() - 2]->type == Instruction::Call &&
           instructions[instructions.size() - 2]->params.ri_params.reg == id;
}

void Bytecode::Optimizer::optimize_tail_calls(Segment &segment) {
    auto &instructions = segment.instructions;
    const size_t number_of_args = instructions[instructions.size() - 2]
                                          ->params.ri_params.intermediate.data.reg;
    instructions.pop_back();// Remove the Return instruction
    instructions.pop_back();// Remove the Call instruction
    instructions.push_back(new (Instruction){
            Instruction::TailCall,
            {.r_param = {number_of_args}},
    });
    instructions.push_back(new (Instruction){Instruction::Return});
}