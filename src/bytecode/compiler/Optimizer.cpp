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
    const size_t old_number_of_instructions = instructions.size() - 1;
    instructions.pop_back();// Remove the Return instruction
    instructions.pop_back();// Remove the Call instruction
    for (size_t i = number_of_args - 1; i != -1; i--)
        instructions.push_back(new (Instruction) {
                Instruction::StoreGlobal,
                {.r_param = {i}},
        });
    instructions.push_back(new (Instruction){
            Instruction::Jump,
            {.r_param = {1}},
    });
    instructions.push_back(new (Instruction){Instruction::Return});

    // Update jump locations
    for (auto &instruction: instructions) {
        if ((instruction->type == Instruction::Jump ||
             instruction->type == Instruction::CondJumpIfNot) &&
            instruction->params.r_param.reg == old_number_of_instructions) {
            instruction->params.r_param.reg = instructions.size() - 1;
        }
    }
}