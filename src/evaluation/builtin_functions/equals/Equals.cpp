#include "Equals.h"
#include "evaluation/Evaluate.h"

static SyntaxTreeNode *False = new SyntaxTreeNode(new Token(Token::Boolean, "#f"));
static SyntaxTreeNode *True = new SyntaxTreeNode(new Token(Token::Boolean, "#t"));

SyntaxTreeNode *Equals::evaluate(const std::vector<SyntaxTreeNode *> &args) {
    for (int i = 1; i < args.size(); i++)
        if (*Evaluate::evaluate(args[i]) != *Evaluate::evaluate(args[i - 1]))
            return False;
    return True;
}
