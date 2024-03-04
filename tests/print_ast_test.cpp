#include "parser/SyntaxTreeNode.h"
#include "utils/OutputSource.h"
#include "utils/printAST.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <memory>

class MockOutputSource final : public OutputSource {
public:
    MOCK_METHOD(void, out, (std::string out), (override));
};


TEST(print_ast_test, ShouldPrintSimpleAST) {
    // (+ 1 2)
    const auto ast = new SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(Token(Token::Number, "1")),
                    new SyntaxTreeNode(Token(Token::Number, "2")),
            });
    const std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);

    EXPECT_CALL(*mockOutputSource, out("-> Node (+)\n"
                                       "\t-> Number (1)\n"
                                       "\t-> Number (2)\n"));
    print_ast(mockOutputSource.get(), *ast);
}

TEST(print_ast_test, ShouldPrintNestedAST) {
    // (+ (* 5 2) 4)
    const auto ast = new SyntaxTreeNode(
            Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(
                            Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(Token(Token::Number, "5")),
                                    new SyntaxTreeNode(Token(Token::Number, "2")),
                            }),
                    new SyntaxTreeNode(Token(Token::Number, "4")),
            });
    const std::string expectedOutput = "-> Node (+)\n"
                                       "\t-> Node (*)\n"
                                       "\t\t-> Number (5)\n"
                                       "\t\t-> Number (2)\n"
                                       "\t-> Number (4)\n";

    std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);

    EXPECT_CALL(*mockOutputSource, out(expectedOutput));
    print_ast(mockOutputSource.get(), *ast);
}
