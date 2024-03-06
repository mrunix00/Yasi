#include "VM.h"

namespace Bytecode {
    VM::VM() {
        local_registers.emplace_back();
        call_stack.emplace_back();
    }

    void VM::setGlobal(const size_t i, const StackObject sObject) {
        if (global_registers.size() < i)
            global_registers.at(i) = sObject;
        else if (global_registers.size() == i)
            global_registers.push_back(sObject);
    }

    StackObject VM::getGlobal(const size_t i) const {
        return global_registers.at(i);
    }

    void VM::newStackFrame(const size_t segment) {
        local_registers.emplace_back();
        StackFrame stackFrame;
        stackFrame.segment = segment;
        stackFrame.current_line = -1;
        call_stack.emplace_back(stackFrame);
    }

    void VM::setLocal(const size_t i, const StackObject sObject) {
        if (const auto registers = &local_registers.back();
            registers->size() < i) {
            registers->at(i) = sObject;
        } else if (registers->size() == i) {
            registers->push_back(sObject);
        }
    }

    void VM::popStackFrame() {
        if (!call_stack.empty())
            call_stack.pop_back();
        if (!local_registers.empty()) {
            local_registers.pop_back();
        }
    }

    void VM::jump(const size_t line) {
        call_stack.back().current_line = line - 1;
    }

    StackObject VM::getLocal(const size_t i) const {
        return local_registers[local_registers.size() - 1][i];
    }
}// namespace Bytecode