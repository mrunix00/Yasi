#include "Interpreter.h"
#include "exceptions/SyntaxError.h"

void Bytecode::Interpreter::execute(const Program &program) {
    const auto &stackTop = vm.call_stack.stackTop;
    for (;; stackTop->current_line++) {
        const auto currentSegment =
                program.segments[stackTop->segment];
        if (stackTop->segment == 0 &&
            stackTop->current_line == currentSegment->instructions.size())
            return;
        const auto currentInstruction =
                currentSegment->instructions[stackTop->current_line];
        switch (currentInstruction->type) {
            case Instruction::Invalid:
                throw SyntaxError("Invalid instruction");
            case Instruction::LoadLiteral:
                vm.program_stack.push(currentInstruction->params.i_param.intermediate);
                break;
            case Instruction::LoadGlobal:
                vm.program_stack.push(vm.getGlobal(currentInstruction->params.r_param.reg));
                break;
            case Instruction::LoadLocal:
                vm.program_stack.push(vm.call_stack.getLocal(currentInstruction->params.r_param.reg));
                break;
            case Instruction::StoreLocal:
                vm.call_stack.setLocal(currentInstruction->params.r_param.reg, vm.program_stack.pop());
                break;
            case Instruction::StoreGlobal:
                vm.setGlobal(currentInstruction->params.r_param.reg, vm.program_stack.pop());
                break;
            case Instruction::Add: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number + object2.data.number);
            } break;
            case Instruction::AddRI: {
                const auto object1 = currentInstruction->params.ri_params.intermediate;
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number + object2.data.number);
            } break;
            case Instruction::AddRR: {
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg1);
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg2);
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"+\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number + object2.data.number);
            } break;
            case Instruction::Subtract: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number - object2.data.number);
            } break;
            case Instruction::SubtractRI: {
                const auto object2 = currentInstruction->params.ri_params.intermediate;
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object1.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number - object2.data.number);
            } break;
            case Instruction::SubtractRR: {
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg1);
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg2);
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number - object2.data.number);
            } break;
            case Instruction::Multiply: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"*\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number * object2.data.number);
            } break;
            case Instruction::MultiplyRI: {
                const auto object1 = currentInstruction->params.ri_params.intermediate;
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"*\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number * object2.data.number);
            } break;
            case Instruction::MultiplyRR: {
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg1);
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.rr_params.reg2);
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"*\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number * object2.data.number);
            } break;
            case Instruction::Increment:
                vm.program_stack.push(vm.program_stack.pop().data.number + 1);
                break;
            case Instruction::Decrement:
                vm.program_stack.push(vm.program_stack.pop().data.number - 1);
                break;
            case Instruction::DecrementR: {
                const auto number = vm.call_stack.getLocal(currentInstruction->params.r_param.reg);
                if (number.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"-\", Expected number, got string");
                }
                vm.program_stack.push(number.data.number - 1);
            } break;
            case Instruction::Divide: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"/\", Expected number, got string");
                }
                if (object2.data.number == 0) {
                    throw SyntaxError("Division by zero", 0, 0);
                }
                vm.program_stack.push(object1.data.number / object2.data.number);
            } break;
            case Instruction::Equals: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"=\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number == object2.data.number);
            } break;
            case Instruction::EqualsRI: {
                const auto object1 = currentInstruction->params.ri_params.intermediate;
                const auto object2 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"=\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number == object2.data.number);
            } break;
            case Instruction::LessThan: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"<\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number < object2.data.number);
            } break;
            case Instruction::LessThanRI: {
                const auto object2 = currentInstruction->params.ri_params.intermediate;
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object1.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \"<\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number < object2.data.number);
            } break;
            case Instruction::GreaterThan: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Number ||
                    object2.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \">\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number > object2.data.number);
            } break;
            case Instruction::GreaterThanRI: {
                const auto object2 = currentInstruction->params.ri_params.intermediate;
                const auto object1 = vm.call_stack.getLocal(currentInstruction->params.ri_params.reg);
                if (object1.type != ObjectType::Number) {
                    throw SyntaxError("Invalid argument type for function \">\", Expected number, got string");
                }
                vm.program_stack.push(object1.data.number > object2.data.number);
            } break;
            case Instruction::And: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Boolean ||
                    object2.type != ObjectType::Boolean) {
                    throw SyntaxError("Invalid argument type for function \"and\", Expected boolean, got string");
                }
                vm.program_stack.push(object1.data.boolean && object2.data.boolean);
            } break;
            case Instruction::Or: {
                const auto object2 = vm.program_stack.pop();
                const auto object1 = vm.program_stack.pop();
                if (object1.type != ObjectType::Boolean ||
                    object2.type != ObjectType::Boolean) {
                    throw SyntaxError("Invalid argument type for function \"or\", Expected boolean, got string");
                }
                vm.program_stack.push(object1.data.boolean || object2.data.boolean);
            } break;
            case Instruction::Not: {
                const auto object = vm.program_stack.pop();
                if (object.type != ObjectType::Boolean)
                    vm.program_stack.push(false);
                else
                    vm.program_stack.push(!object.data.boolean);
            } break;
            case Instruction::CondJumpIfNot: {
                const auto cond = vm.program_stack.pop();
                if (!cond.data.boolean)
                    vm.call_stack.stackTop->current_line = currentInstruction->params.r_param.reg - 1;
            } break;
            case Instruction::Jump: {
                vm.call_stack.stackTop->current_line = currentInstruction->params.r_param.reg - 1;
            } break;
            case Instruction::Call: {
                vm.call_stack.newStackFrame(
                        currentInstruction->params.ri_params.reg,
                        currentInstruction->params.ri_params.intermediate.data.reg,
                        &vm.program_stack);
            } break;
            case Instruction::CallLambda: {
                const auto lambda = vm.program_stack.pop();
                vm.call_stack.newStackFrame(
                        lambda.data.reg,
                        currentInstruction->params.r_param.reg,
                        &vm.program_stack);
            } break;
            case Instruction::Return:
                vm.call_stack.popStackFrame();
                break;
            case Instruction::ReadFromStdin: {
                std::string input;
                std::getline(std::cin, input);
                char *p;
                double number = std::strtod(input.c_str(), &p);
                if (*p)
                    vm.program_stack.push(input);
                else
                    vm.program_stack.push(number);
            } break;
            case Instruction::SendToStdout:
                std::cout << vm.program_stack.pop().toString();
                break;
        }
    }
}
