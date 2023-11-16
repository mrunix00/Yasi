#include <gtest/gtest.h>
#include "../src/Tokens/Tokens.h"

TEST(token_test, ShouldCompareTokens) {
    auto token1 = OpenBracket();
    auto token2 = OpenBracket();
    auto token3 = Symbol("+");
    auto token4 = Symbol("-");

    EXPECT_EQ(token1 == token2, true);
    EXPECT_EQ(token2 == token3, false);
    EXPECT_EQ(token3 == token4, false);
}

TEST(token_test, BracketsTest) {
    auto openBracket = OpenBracket();
    auto closedBracket = ClosedBracket();
    EXPECT_EQ(openBracket.symbol, "(");
    EXPECT_EQ(closedBracket.symbol, ")");
}

TEST(token_test, IntegersTest) {
    auto integer1 = Integer(69);
    EXPECT_EQ(integer1.symbol, "69");
}