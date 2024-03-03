#include "bytecode/instructions/Equals.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_equals_test, ShouldReturnTrueOnEquality) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(10),
                    new Equals(),
            }),
    });

    const auto expected_result = StackObject(true);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_equals_test, ShouldReturnFalseOnInequality) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(20),
                    new LoadLiteral(10),
                    new Equals(),
            }),
    });

    const auto expected_result = StackObject(false);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_equals_test, ShouldCompareTwoDecimalNumbersAndReturnTrueOnEquality) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.5),
                    new LoadLiteral(3.5),
                    new Equals(),
            }),
    });

    const auto expected_result = StackObject(true);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_equals_test, ShouldCompareTwoDecimalNumbersAndReturnFalseOnInequality) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.5),
                    new LoadLiteral(3.14),
                    new Equals(),
            }),
    });

    const auto expected_result = StackObject(false);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}
