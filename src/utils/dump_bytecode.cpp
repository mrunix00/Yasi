#include "dump_bytecode.h"

void print_instruction(const Bytecode::Instruction &instruction) {
    switch (instruction.type) {
        case Bytecode::Instruction::LoadLiteral:
            if (instruction.params.i_param.intermediate.type == Bytecode::String) {
                const auto str = !strcmp(instruction.params.i_param.intermediate.data.string, "\n")
                                         ? std::string("\\n")
                                         : instruction.params.i_param.intermediate.toString();
                std::cout << "LoadLiteral \"" << str << "\"\n";
            } else
                std::cout << "LoadLiteral " << instruction.params.i_param.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::LoadLocal:
            std::cout << "LoadLocal $r" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::LoadGlobal:
            std::cout << "LoadGlobal $g" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::Add:
            std::cout << "Add\n";
            break;
        case Bytecode::Instruction::AddRI:
            std::cout << "AddRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::AddRR:
            std::cout << "AddRR $r" << instruction.params.rr_params.reg1 << " $r" << instruction.params.rr_params.reg2 << '\n';
            break;
        case Bytecode::Instruction::Subtract:
            std::cout << "Subtract\n";
            break;
        case Bytecode::Instruction::SubtractRI:
            std::cout << "SubtractRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::SubtractRR:
            std::cout << "SubtractRR $r" << instruction.params.rr_params.reg1 << " $r" << instruction.params.rr_params.reg2 << '\n';
            break;
        case Bytecode::Instruction::Multiply:
            std::cout << "Multiply\n";
            break;
        case Bytecode::Instruction::MultiplyRI:
            std::cout << "MultiplyRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::MultiplyRR:
            std::cout << "MultiplyRR $r" << instruction.params.rr_params.reg1 << " $r" << instruction.params.rr_params.reg2 << '\n';
            break;
        case Bytecode::Instruction::Divide:
            std::cout << "Divide\n";
            break;
        case Bytecode::Instruction::DivideRI:
            std::cout << "DivideRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::DivideRR:
            std::cout << "DivideRR $r" << instruction.params.rr_params.reg1 << " $r" << instruction.params.rr_params.reg2 << '\n';
            break;
        case Bytecode::Instruction::Increment:
            std::cout << "Increment\n";
            break;
        case Bytecode::Instruction::Decrement:
            std::cout << "Decrement\n";
            break;
        case Bytecode::Instruction::DecrementR:
            std::cout << "DecrementR $r" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::Equals:
            std::cout << "Equals\n";
            break;
        case Bytecode::Instruction::EqualsRI:
            std::cout << "EqualsRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::LessThan:
            std::cout << "LessThan\n";
            break;
        case Bytecode::Instruction::LessThanRI:
            std::cout << "LessThanRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::GreaterThan:
            std::cout << "GreaterThan\n";
            break;
        case Bytecode::Instruction::GreaterThanRI:
            std::cout << "GreaterThanRI $r" << instruction.params.ri_params.reg << " " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::Not:
            std::cout << "Not\n";
            break;
        case Bytecode::Instruction::Call:
            std::cout << "Call :" << instruction.params.ri_params.reg << ", " << instruction.params.ri_params.intermediate.toString() << '\n';
            break;
        case Bytecode::Instruction::CallLambda:
            std::cout << "CallLambda :" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::TailCall:
            std::cout << "TailCall " << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::CondJumpIfNot:
            std::cout << "CondJumpIfNot :" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::Jump:
            std::cout << "Jump :" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::StoreGlobal:
            std::cout << "StoreGlobal $g" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::SendToStdout:
            std::cout << "SendToStdout\n";
            break;
        case Bytecode::Instruction::ReadFromStdin:
            std::cout << "ReadFromStdin\n";
            break;
        case Bytecode::Instruction::Or:
            std::cout << "Or\n";
            break;
        case Bytecode::Instruction::And:
            std::cout << "And\n";
            break;
        case Bytecode::Instruction::Return:
            std::cout << "Return\n";
            break;
        case Bytecode::Instruction::StoreLocal:
            std::cout << "StoreLocal $r" << instruction.params.r_param.reg << '\n';
            break;
        case Bytecode::Instruction::Invalid:
            std::cout << "Invalid Instruction\n";
            break;
        default:
            std::cout << "Unknown instruction\n";
    }
}

void dump_bytecode(const Bytecode::Program &program) {
    for (size_t i = 0; i < program.segments.size(); i++) {
        std::cout << "Segment :" << i << "\n";
        for (size_t j = 0; j < program.segments[i]->instructions.size(); j++) {
            std::cout << j << '\t';
            print_instruction(*program.segments[i]->instructions[j]);
        }
        std::cout << '\n';
    }
}
