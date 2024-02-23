#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Divide.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_divide_test, ShouldDivideTwoLiterals) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(30),
                    new LoadLiteral(2),
                    new Divide(),
            }),
    });

    const auto expected_result = new StackObject(new DecimalNumberLiteral(15));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_divide_test, ShouldDivideTwoDecimalNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(4.5)),
                    new LoadLiteral(new DecimalNumberLiteral(1.5)),
                    new Divide(),
            }),
    });

    const auto expected_result = new StackObject(
            new DecimalNumberLiteral(3));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_divide_test, ShouldAddDecimalAndIntegerNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(4.5)),
                    new LoadLiteral(2),
                    new Divide(),
            }),
    });

    const auto expected_result = new StackObject(
            new DecimalNumberLiteral(2.25));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}
