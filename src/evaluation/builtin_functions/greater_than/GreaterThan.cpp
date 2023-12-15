#include "GreaterThan.h"
#include "evaluation/Evaluate.h"
#include "parser/SyntaxTreeNode.h"
#include <vector>

static SyntaxTreeNode *False = new SyntaxTreeNode(new Token(Token::Boolean, "#f"));
static SyntaxTreeNode *True = new SyntaxTreeNode(new Token(Token::Boolean, "#t"));

SyntaxTreeNode* GreaterThan::evaluate(const std::vector<SyntaxTreeNode*> &args) {
    for (int i = 1; i < args.size(); i++) {
        Token token1 = *Evaluate::evaluate(args[i - 1])->token;
        Token token2 = *Evaluate::evaluate(args[i])->token;
        if (token1.asDecimal() <= token2.asDecimal())
            return False;
    }
    return True;
}
