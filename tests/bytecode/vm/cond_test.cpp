#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/CondJumpIfNot.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/Jump.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_cond_test, ShouldNotJumpOnTrueCondition) {
    const auto program = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(5),
                            new LoadLiteral(20),
                    }),
            });

    const auto expected_result = StackObject((double) 20);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_cond_test, ShouldJumpOnFalseCondition) {
    const auto program = Program(
            {
                    new Segment({
                            new LoadLiteral(10),
                            new LoadLiteral(20),
                            new GreaterThan(),
                            new CondJumpIfNot(5),
                            new LoadLiteral(10),
                    }),
            });

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), StackObject());
}

TEST(vm_conf_test, ShouldJumpToOppositeCondition) {
    const auto program = Program(
            {
                    new Segment({
                            new LoadLiteral(20),
                            new LoadLiteral(10),
                            new GreaterThan(),
                            new CondJumpIfNot(6),
                            new LoadLiteral(20),
                            new Jump(7),
                            new LoadLiteral(10),
                    }),
            });

    const auto expected_result = StackObject((double) 20);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}
