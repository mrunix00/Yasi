#ifndef YASI_CALL_H
#define YASI_CALL_H

#include "Instruction.h"
namespace Bytecode {
    class Call final : public Instruction {
        size_t segment;

    public:
        explicit Call(const size_t segment) : segment(segment) { type = InstructionType::Call; }
        void execute(VM *vm) override {}
        [[nodiscard]] std::string toString() const override {
            return "Call :" + std::to_string(segment);
        }
        bool operator==(const Instruction &instruction) const override {
            return instruction.type == type &&
                   dynamic_cast<const Call *>(&instruction)->segment == segment;
        }
    };
}// namespace Bytecode

#endif//YASI_CALL_H
