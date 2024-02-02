#include "bytecode/compiler/Program.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/vm/Interpreter.h"
#include "bytecode/vm/Literal.h"
#include "bytecode/vm/StackObject.h"
#include "bytecode/vm/VM.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(load_test, ShouldPushLiteralIntoStack) {
    const auto program = Program({
            new Segment({new LoadLiteral(10)}),
    });

    const auto expected_result = new StackObject(new Literal(10));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.StackTop() == *expected_result, true);
}