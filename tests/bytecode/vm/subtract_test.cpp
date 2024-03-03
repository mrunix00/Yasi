#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Subtract.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_subtract_test, ShouldSubtractTwoLiterals) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(30),
                    new LoadLiteral(20),
                    new Subtract(),
            }),
    });

    const auto expected_result = StackObject((double) 10);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_subtract_test, ShouldSubtractTwoDecimalNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.1415),
                    new LoadLiteral(1.1),
                    new Subtract(),
            }),
    });

    const auto expected_result = StackObject(2.0415);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_subtract_test, ShouldSubtractDecimalAndIntegerNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.1415),
                    new LoadLiteral(2),
                    new Subtract(),
            }),
    });

    const auto expected_result = StackObject(1.1415);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}
