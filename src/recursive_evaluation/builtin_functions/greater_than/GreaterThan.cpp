#include "GreaterThan.h"
#include "parser/SyntaxTreeNode.h"
#include "recursive_evaluation/RecursiveEvaluation.h"
#include <vector>

static SyntaxTreeNode *False = new SyntaxTreeNode(new Token(Token::Boolean, new std::string("#f")));
static SyntaxTreeNode *True = new SyntaxTreeNode(new Token(Token::Boolean, new std::string("#t")));

namespace RecursiveEvaluation {
    SyntaxTreeNode *GreaterThan::evaluate(const std::vector<SyntaxTreeNode *> &args) {
        for (int i = 1; i < args.size(); i++) {
            Token token1 = *RecursiveEvaluation::evaluate(args[i - 1])->token;
            Token token2 = *RecursiveEvaluation::evaluate(args[i])->token;
            if (token1.asDecimal() <= token2.asDecimal())
                return False;
        }
        return True;
    }
}