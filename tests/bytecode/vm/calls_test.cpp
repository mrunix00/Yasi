#include "bytecode/compiler/Program.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/Subtract.h"
#include "bytecode/vm/Interpreter.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(vm_calls_test, function_with_a_single_arg) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(10),
                    new Call(1, 1),
            }),
            new Segment({
                    new Load(new LocalRegister(0)),
                    new Load(new LocalRegister(0)),
                    new Multiply(),
            }),
    });

    const auto expected_result = NumberLiteral(100);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == expected_result, true);
}

TEST(vm_calls_test, function_with_multiple_args) {
    const auto program = Program({
            new Segment({
                    new LoadLiteral(50),
                    new LoadLiteral(10),
                    new Call(1, 2),
            }),
            new Segment({
                    new Load(new LocalRegister(0)),
                    new Load(new LocalRegister(1)),
                    new Subtract(),
            }),
    });

    const auto expected_result = NumberLiteral(40);

    auto interpreter = Interpreter();
    interpreter.execute(program);

    EXPECT_EQ(*interpreter.vm.stackTop() == expected_result, true);
}