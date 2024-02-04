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

    const auto expected_result = new StackObject(new Literal(Boolean::True));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_greater_than, ShouldReturnFalseWhenNotGreaterThan) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new GreaterThan(),
            }),
    });

    const auto expected_result = new StackObject(new Literal(Boolean::False));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}
