#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_greater_than, ShouldReturnTrueWhenGreaterThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(20),
                    new LoadLiteral(10),
                    new GreaterThan(),
            }),
    });

    const auto expected_result = StackObject(true);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_greater_than, ShouldReturnFalseWhenNotGreaterThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new GreaterThan(),
            }),
    });

    const auto expected_result = StackObject(false);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_greater_than, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenGreaterThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.5),
                    new LoadLiteral(3.4),
                    new GreaterThan(),
            }),
    });

    const auto expected_result = StackObject(true);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_greater_than, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotGreaterThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.01),
                    new LoadLiteral(3.14),
                    new GreaterThan(),
            }),
    });

    const auto expected_result = StackObject(false);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}
