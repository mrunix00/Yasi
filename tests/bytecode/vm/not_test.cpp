#include "bytecode/compiler/Program.h"
#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Not.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_not_test, ShouldNegateATrueCondition) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(10),
                    new Equals(),
                    new Not(),
            }),
    });

    const auto expected_result = BooleanLiteral(false);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == expected_result, true);
}

TEST(vm_not_test, ShouldNegateAFalseCondition) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new Equals(),
                    new Not(),
            }),
    });

    const auto expected_result = BooleanLiteral(true);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == expected_result, true);
}