#include "bytecode/compiler/Program.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/StoreGlobal.h"
#include "bytecode/objects/StackObject.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_load_test, ShouldLoadLiteralIntoStack) {
    const auto program = Program({
            new Segment({new LoadLiteral(10)}),
    });

    const auto expected_result = StackObject((double) 10);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}

TEST(vm_load_test, ShouldLoadGlobalVariableIntoStack) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new StoreGlobal(0),
                    new LoadGlobal(0),
            }),
    });

    const auto expected_result = StackObject((double) 10);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(interpreter.vm.program_stack.top(), expected_result);
}