#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Divide.h"
#include "bytecode/instructions/Equals.h"
#include "bytecode/instructions/GreaterThan.h"
#include "bytecode/instructions/LessThan.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/LoadLocal.h"
#include "bytecode/instructions/Multiply.h"
#include "bytecode/instructions/Store.h"
#include "bytecode/instructions/Subtract.h"
#include <gtest/gtest.h>

using namespace Bytecode;

TEST(instruction_to_string, add) {
    const auto instruction = Add();
    const auto expected_result = "Add";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, subtract) {
    const auto instruction = Subtract();
    const auto expected_result = "Subtract";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, multiply) {
    const auto instruction = Multiply();
    const auto expected_result = "Multiply";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, divide) {
    const auto instruction = Divide();
    const auto expected_result = "Divide";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, load) {
    const auto instruction = LoadLocal(1);
    const auto expected_result = "LoadLocal $r1";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, load_literal) {
    const auto instruction = LoadLiteral(69);
    const auto expected_result = "LoadLiteral 69";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, store) {
    const auto instruction = Store(new LocalRegister(12));
    const auto expected_result = "Store $r12";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, equals) {
    const auto instruction = Equals();
    const auto expected_result = "Equals";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, greater) {
    const auto instruction = GreaterThan();
    const auto expected_result = "GreaterThan";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}

TEST(instruction_to_string, less) {
    const auto instruction = LessThan();
    const auto expected_result = "LessThan";
    const auto actual_result = instruction.toString();
    EXPECT_EQ(expected_result, actual_result);
}
