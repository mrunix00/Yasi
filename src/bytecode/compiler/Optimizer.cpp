#include "Optimizer.h"
#include <algorithm>

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

bool Bytecode::Optimizer::is_inlineable(const Bytecode::Segment &segment, size_t id) {
    return std::none_of(
            segment.instructions.begin(),
            segment.instructions.end(),
            [id](Bytecode::Instruction *instruction) {
                return (instruction->type == Bytecode::Instruction::Call &&
                        instruction->params.ri_params.reg == id) ||
                       // TODO: Fix tail calls later
                       instruction->type == Bytecode::Instruction::TailCall;
            });
}

/* This code is fucking garbage!
 * TODO: Clean this shit up */
void Bytecode::Optimizer::inline_function(
        Bytecode::Segment &segment,
        Bytecode::Segment &to_inline,
        size_t id) {
    size_t inside_offset = 0;
    size_t outside_offset = 0;
    for (auto current_instruction = segment.instructions.begin();
         current_instruction != segment.instructions.end();
         std::advance(current_instruction, 1)) {
        if ((*current_instruction)->type == Instruction::Call &&
            (*current_instruction)->params.ri_params.reg == id) {
            auto number_of_args = (*current_instruction)->params.ri_params.intermediate.data.reg;
            current_instruction = segment.instructions.erase(current_instruction);

            // Load function arguments
            for (size_t i = number_of_args - 1; i != -1; i--) {
                auto load_instruction = new Instruction{
                        Instruction::StoreLocal,
                        {.r_param = {i}},
                };
                current_instruction = segment.instructions.insert(current_instruction, load_instruction);
                std::advance(current_instruction, 1);
            }
            inside_offset = current_instruction - segment.instructions.begin();

            // inline the function
            for (auto new_instruction: to_inline.instructions) {
                if (new_instruction->type == Instruction::Return)
                    break;
                if (new_instruction->type == Instruction::Jump ||
                    new_instruction->type == Instruction::CondJumpIfNot) {
                    // Align jump locations inside the function
                    auto jump_instruction = new Instruction{
                            new_instruction->type,
                            {.r_param = {new_instruction->params.r_param.reg + inside_offset}},
                    };
                    current_instruction = segment.instructions.insert(current_instruction, jump_instruction);
                } else {
                    current_instruction = segment.instructions.insert(current_instruction, new_instruction);
                }
                std::advance(current_instruction, 1);
                outside_offset++;
            }
            if (current_instruction == segment.instructions.end())
                break;
        }

        // Align jump locations outside the function
        if ((*current_instruction)->type == Instruction::Jump ||
            (*current_instruction)->type == Instruction::CondJumpIfNot) {
            (*current_instruction)->params.r_param.reg += outside_offset;
        }
    }
}
