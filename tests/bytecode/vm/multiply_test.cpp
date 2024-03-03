#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_multiply_test, ShouldMultiplyTwoLiterals) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new Multiply(),
            }),
    });

    const auto expected_result = StackObject((double) 200);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_multiply_test, ShouldMultiplyTwoDecimalNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.1415),
                    new LoadLiteral(1.1),
                    new Multiply(),
            }),
    });

    const auto expected_result = StackObject(3.45565);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_multiply_test, ShouldMultiplyDecimalAndIntegerNumbers) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(3.1415),
                    new LoadLiteral(2),
                    new Multiply(),
            }),
    });

    const auto expected_result = StackObject(6.283);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}
