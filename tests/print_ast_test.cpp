#include "parser/SyntaxTreeNode.h"
#include "utils/OutputSource.h"
#include "utils/printAST.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class MockOutputSource : public OutputSource {
public:
    MOCK_METHOD(void, out, (std::string out), (override));
};


TEST(print_ast_test, ShouldPrintSimpleAST) {
    // (+ 1 2)
    const auto ast = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(new Token(Token::Integer, "1")),
                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
            });
    std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);

    EXPECT_CALL(*mockOutputSource, out("-> Node (+)\n"
                                       "\t-> Integer (1)\n"
                                       "\t-> Integer (2)\n"));
    print_ast(mockOutputSource.get(), *ast);
}

TEST(print_ast_test, ShouldPrintNestedAST) {
    // (+ (* 5 2) 4)
    const auto ast = new SyntaxTreeNode(
            new Token(Token::Symbol, "+"),
            {
                    new SyntaxTreeNode(
                            new Token(Token::Symbol, "*"),
                            {
                                    new SyntaxTreeNode(new Token(Token::Integer, "5")),
                                    new SyntaxTreeNode(new Token(Token::Integer, "2")),
                            }),
                    new SyntaxTreeNode(new Token(Token::Integer, "4")),
            });
    const std::string expectedOutput = "-> Node (+)\n"
                                       "\t-> Node (*)\n"
                                       "\t\t-> Integer (5)\n"
                                       "\t\t-> Integer (2)\n"
                                       "\t-> Integer (4)\n";

    std::shared_ptr<MockOutputSource> mockOutputSource(new MockOutputSource);

    EXPECT_CALL(*mockOutputSource, out(expectedOutput));
    print_ast(mockOutputSource.get(), *ast);
}
