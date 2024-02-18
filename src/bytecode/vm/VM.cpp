#include "VM.h"
namespace Bytecode {
    StackObject* VM::stackTop() const {
        if (program_stack.empty()) return nullptr;
        return program_stack.back();
    }
    void VM::stackPush(StackObject *object) {
        program_stack.push_back(object);
    }
    StackObject* VM::stackPop() {
        auto object = program_stack.back();
        program_stack.pop_back();
        return object;
    }

    void VM::setGlobal(const size_t i, StackObject *sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }
    StackObject* VM::getGlobal(const size_t i) const {
        return global_registers.at(i);
    }

    void VM::jump(size_t line) {
        call_stack.back().current_line = line - 1;
    }
    void VM::clearStack() {
        program_stack.clear();
    }

    void VM::newStackFrame(size_t segment) {
        local_registers.emplace_back();
        StackFrame stackFrame;
        stackFrame.segment = segment;
        stackFrame.current_line = -1;
        call_stack.emplace_back(stackFrame);
    }

    void VM::setLocal(size_t i, StackObject *sObject) {
        auto registers = &local_registers[local_registers.size() - 1];
        if (registers->size() < i)
            registers->at(i) = sObject;
        else if (registers->size() == i)
            registers->push_back(sObject);
    }

    StackObject *VM::getLocal(size_t i) {
        return local_registers[local_registers.size() - 1][i];
    }
    size_t VM::getCurrentLine() {
        return call_stack.back().current_line;
    }
    size_t VM::getCurrentSegment() {
        return call_stack.back().segment;
    }
    void VM::nextLine() {
        call_stack.back().current_line++;
    }
    void VM::popStackFrame() {
        if (!call_stack.empty())
            call_stack.pop_back();
        if (!local_registers.empty())
            local_registers.pop_back();
    }
}// namespace Bytecode