#include "VM.h"
namespace Bytecode {
    void VM::setGlobal(const size_t i, StackObject sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }
    StackObject VM::getGlobal(const size_t i) const {
        return global_registers.at(i);
    }

    void VM::newStackFrame(size_t segment) {
        local_registers.emplace_back();
        StackFrame stackFrame;
        stackFrame.segment = segment;
        stackFrame.current_line = -1;
        call_stack.emplace_back(stackFrame);
    }

    void VM::setLocal(size_t i, StackObject sObject) {
        auto registers = &local_registers[local_registers.size() - 1];
        if (registers->size() < i)
            registers->at(i) = sObject;
        else if (registers->size() == i)
            registers->push_back(sObject);
    }

    void VM::popStackFrame() {
        if (!call_stack.empty())
            call_stack.pop_back();
        if (!local_registers.empty()) {
            local_registers.pop_back();
        }
    }
}// namespace Bytecode