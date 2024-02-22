#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_add_test, ShouldAddTwoLiterals) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new Add(),
            }),
    });

    const auto expected_result = new StackObject(new NumberLiteral(30));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_add_test, ShouldAddTwoDecimalNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(3.1415)),
                    new LoadLiteral(new DecimalNumberLiteral(1.5)),
                    new Add(),
            }),
    });

    const auto expected_result = new StackObject(
            new DecimalNumberLiteral(4.6415));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_add_test, ShouldAddDecimalAndIntegerNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(new DecimalNumberLiteral(3.1415)),
                    new LoadLiteral(1),
                    new Add(),
            }),
    });

    const auto expected_result = new StackObject(
            new DecimalNumberLiteral(4.1415));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}
