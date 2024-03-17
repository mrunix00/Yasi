#include "Interpreter.h"

#include <iostream>

void Bytecode::Interpreter::execute(const Program &program) {
    while (true) {
        const auto currentLine = vm.call_stack.stackTop->current_line;
        const auto currentSegment = vm.call_stack.stackTop->segment;
        if (currentSegment == 0 &&
            currentLine == program.segments[0]->instructions.size()) {
            break;
        }
        const auto currentInstruction = program.segments[currentSegment]
                                                ->instructions[currentLine];
        if (currentLine == program.segments[currentSegment]->instructions.size()) {
            vm.call_stack.popStackFrame();
        } else {
            switch (currentInstruction->type) {
                case InstructionType::Add:
                    vm.program_stack.push(
                            vm.program_stack.pop().asNumber() +
                            vm.program_stack.pop().asNumber());
                    break;
                case InstructionType::Subtract: {
                    const auto object2 = vm.program_stack.pop();
                    const auto object1 = vm.program_stack.pop();
                    vm.program_stack.push(object1.asNumber() - object2.asNumber());
                } break;
                case InstructionType::Multiply:
                    vm.program_stack.push(
                            vm.program_stack.pop().asNumber() *
                            vm.program_stack.pop().asNumber());
                    break;
                case InstructionType::Divide: {
                    const auto object2 = vm.program_stack.pop();
                    const auto object1 = vm.program_stack.pop();
                    vm.program_stack.push(object1.asNumber() / object2.asNumber());
                } break;
                case InstructionType::Equals: {
                    const auto object2 = vm.program_stack.pop();
                    const auto object1 = vm.program_stack.pop();
                    vm.program_stack.push(object1.asNumber() == object2.asNumber());
                } break;
                case InstructionType::LessThan: {
                    const auto object2 = vm.program_stack.pop();
                    const auto object1 = vm.program_stack.pop();
                    vm.program_stack.push(object1.asNumber() < object2.asNumber());
                } break;
                case InstructionType::GreaterThan: {
                    const auto object2 = vm.program_stack.pop();
                    const auto object1 = vm.program_stack.pop();
                    vm.program_stack.push(object1.asNumber() > object2.asNumber());
                } break;
                case InstructionType::Not:
                    vm.program_stack.push(!vm.program_stack.pop().asBoolean());
                    break;
                case InstructionType::LoadLiteral:
                    vm.program_stack.push(currentInstruction->literal);
                    break;
                case InstructionType::LoadLocal:
                    vm.program_stack.push(vm.call_stack.getLocal(
                            currentInstruction->reg));
                    break;
                case InstructionType::LoadGlobal:
                    vm.program_stack.push(vm.getGlobal(
                            currentInstruction->reg));
                    break;
                case InstructionType::StoreGlobal:
                    vm.setGlobal(currentInstruction->reg, vm.program_stack.pop());
                    break;
                case InstructionType::CondJumpIfNot:
                    if (const auto cond = vm.program_stack.pop();
                        !cond.asBoolean())
                        vm.call_stack.stackTop->current_line = currentInstruction->param - 1;
                    break;
                case InstructionType::Jump:
                    vm.call_stack.stackTop->current_line = currentInstruction->param - 1;
                    break;
                case InstructionType::Call:
                    vm.call_stack.newStackFrame(
                            currentInstruction->reg,
                            currentInstruction->param,
                            &vm.program_stack);
                    break;
                case InstructionType::CallLambda: {
                    const auto lambda = vm.program_stack.pop();
                    vm.call_stack.newStackFrame(
                            lambda.asLambda(),
                            currentInstruction->param,
                            &vm.program_stack);
                } break;
                case InstructionType::SendToStdout:
                    std::cout << vm.program_stack.pop().toString();
                    break;
                default:
                    throw;
            }
        }
        vm.call_stack.stackTop->current_line++;
    }
}
