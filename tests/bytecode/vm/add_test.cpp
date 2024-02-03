#include "bytecode/compiler/Segment.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(add_test, ShouldAddTwoLiterals) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new LoadLiteral(20),
                    new Add(),
            }),
    });

    const auto expected_result = new StackObject(new Literal(30));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}