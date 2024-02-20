#include "bytecode/compiler/Program.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/vm/Interpreter.h"
#include "bytecode/vm/Literal.h"
#include "bytecode/vm/StackObject.h"
#include "bytecode/vm/VM.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_load_test, ShouldLoadLiteralIntoStack) {
    const auto program = Program({
            new Segment({new LoadLiteral(10)}),
    });

    const auto expected_result = new StackObject(new Literal(10));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}

TEST(vm_load_test, ShouldLoadGlobalVariableIntoStack) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new Store(new GlobalRegister(0)),
                    new Load(new GlobalRegister(0)),
            }),
    });

    const auto expected_result = new StackObject(new Literal(10));

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == *expected_result, true);
}