#include "printAST.h"
#include "parser/SyntaxTreeNode.h"
#include <string>

std::string parse_ast(SyntaxTreeNode ast, int level) {
    std::string output;
    std::string tabs;

    for (int i = 0; i < level; i++) tabs = tabs + "\t";
    tabs = tabs + "-> ";

    if (!ast.children.empty()) {
        output = tabs + "Node (" + ast.token.token + ")\n";
    } else {
        std::string type;
        if (ast.token.type == Token::Integer) type = "Integer";
        else if (ast.token.type == Token::Decimal)
            type = "Decimal";
        else if (ast.token.type == Token::String)
            type = "String";
        else
            type = "Symbol";
        return tabs + type + " (" + ast.token.token + ")\n";
    }

    for (const auto child: ast.children) {
        output = output + parse_ast(child, level + 1);
    }

    return output;
}

void print_ast(OutputSource *outputSource, SyntaxTreeNode ast) {
    outputSource->out(parse_ast(ast, 0));
}
