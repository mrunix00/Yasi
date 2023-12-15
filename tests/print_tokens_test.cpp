#include "lexer/Lexer.h"
#include "utils/OutputSource.h"
#include "utils/printTokens.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockOutputSource : public OutputSource {
public:
    MOCK_METHOD(void, out, (std::string out), (override));
};

TEST(print_tokens, ShouldPrintTokens) {
    // (+ 1 2)
    const std::vector sample = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "+"),
            new Token(Token::Integer, "1"),
            new Token(Token::Integer, "2"),
            new Token(Token::ClosedBracket, ")"),
    };

    std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);
    EXPECT_CALL(*mockOutputSource, out("['(', '+', 1, 2, ')']"));

    printTokens(mockOutputSource.get(), sample);
}

TEST(print_tokens, ShouldPrintStringTokens) {
    // (print "Hello World")
    const std::vector sample = {
            new Token(Token::OpenBracket, "("),
            new Token(Token::Symbol, "print"),
            new Token(Token::String, "\"Hello World\""),
            new Token(Token::ClosedBracket, ")"),
    };

    std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);
    EXPECT_CALL(*mockOutputSource, out("['(', 'print', \"Hello World\", ')']"));

    printTokens(mockOutputSource.get(), sample);

}
