#include "Interpreter.h"
#include "exceptions/SyntaxError.h"

#include <algorithm>
#include <iostream>

void Bytecode::Interpreter::execute(const Program &program) {
    const auto &stackTop = vm.call_stack.stackTop;
    for (;; stackTop->current_line++) {
        const auto currentSegment =
                program.segments[stackTop->segment];
        if (stackTop->segment == 0
            && stackTop->current_line == currentSegment->instructions.size())
            return;
        const auto currentInstruction =
                currentSegment->instructions[stackTop->current_line];

        switch (currentInstruction->type) {
            case InstructionType::Add: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() + object2.asNumber());
            } break;
            case InstructionType::Subtract: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() - object2.asNumber());
            } break;
            case InstructionType::Multiply: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"*\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() * object2.asNumber());
            } break;
            case InstructionType::Divide: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"/\", Expected number, got string");
                }
                if (object2.asNumber() == 0) {
                    throw SyntaxError("Division by zero", 0, 0);
                }
                vm.program_stack.push(object1.asNumber() / object2.asNumber());
            } break;
            case InstructionType::Equals: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"=\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() == object2.asNumber());
            } break;
            case InstructionType::LessThan: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"<\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() < object2.asNumber());
            } break;
            case InstructionType::GreaterThan: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \">\", Expected number, got string");
                }
                vm.program_stack.push(object1.asNumber() > object2.asNumber());
            } break;
            case InstructionType::Not: {
                const auto object = vm.program_stack.pop();
                if (object.type != ObjectType::Boolean)
                    vm.program_stack.push(false);
                else
                    vm.program_stack.push(!object.asBoolean());
            } break;
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
                    stackTop->current_line = currentInstruction->param - 1;
                break;
            case InstructionType::Jump:
                stackTop->current_line = currentInstruction->param - 1;
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
            case InstructionType::ReadFromStdin: {
                std::string input;
                std::getline(std::cin, input);
                char *p;
                double number = std::strtod(input.c_str(), &p);
                if (*p)
                    vm.program_stack.push(input);
                else
                    vm.program_stack.push(number);
            } break;
            case InstructionType::Or: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Boolean ||
                    object2.type != ObjectType::Boolean) {
                    throw SyntaxError("Invalid argument type for function \"or\", Expected boolean, got string");
                }
                vm.program_stack.push(object1.asBoolean() || object2.asBoolean());
            } break;
            case InstructionType::And: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Boolean ||
                    object2.type != ObjectType::Boolean) {
                    throw SyntaxError("Invalid argument type for function \"and\", Expected boolean, got string");
                }
                vm.program_stack.push(object1.asBoolean() && object2.asBoolean());
            } break;
            case InstructionType::Return:
                vm.call_stack.popStackFrame();
                break;
            default:
                throw;
        }
    }
}
