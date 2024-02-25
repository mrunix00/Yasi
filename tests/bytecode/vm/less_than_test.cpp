#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_less_than, ShouldReturnTrueWhenLessThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new LessThan(),
            }),
    });

    const auto expected_result = new StackObject(new BooleanLiteral(true));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_less_than, ShouldReturnFalseWhenNotLessThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(20),
                    new LoadLiteral(10),
                    new LessThan(),
            }),
    });

    const auto expected_result = new StackObject(new BooleanLiteral(false));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_less_than, ShouldCompareTwoDecimalNumbersAndReturnTrueWhenLessThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(3.4)),
                    new LoadLiteral(new DecimalNumberLiteral(3.5)),
                    new LessThan(),
            }),
    });

    const auto expected_result = new StackObject(new BooleanLiteral(true));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_less_than, ShouldCompareTwoDecimalNumbersAndReturnFalseWhenNotLessThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(3.14)),
                    new LoadLiteral(new DecimalNumberLiteral(3.01)),
                    new LessThan(),
            }),
    });

    const auto expected_result = new StackObject(new BooleanLiteral(false));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}
