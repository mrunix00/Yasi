#include "LessThan.h"
#include "evaluation/Evaluate.h"

static SyntaxTreeNode *False = new SyntaxTreeNode(new Token(Token::Boolean, new std::string("#f")));
static SyntaxTreeNode *True = new SyntaxTreeNode(new Token(Token::Boolean, new std::string("#t")));

SyntaxTreeNode *LessThan::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    for (int i = 1; i < args.size(); i++) {
        Token token1 = *Evaluate::evaluate(args[i - 1])->token;
        Token token2 = *Evaluate::evaluate(args[i])->token;
        if (token1.asDecimal() >= token2.asDecimal())
            return False;
    }
    return True;
}
