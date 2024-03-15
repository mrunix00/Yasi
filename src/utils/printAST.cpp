#include "parser/SyntaxTreeNode.h"
#include <iostream>
#include <string>

std::string parse_ast(const SyntaxTreeNode &ast, int level) {
    std::string output;
    std::string tabs;

    for (int i = 0; i < level; i++) tabs += "\t";
    tabs = tabs + "-> ";

    if (ast.type == SyntaxTreeNode::Expression) {
        output = tabs + "Expression (" + ((Expression *) &ast)->getName() + ")\n";
    } else {
        std::string type;
        if (((TokenNode*) &ast)->getType() == Token::Number)
            type = "Number";
        else if (((TokenNode*) &ast)->getType() == Token::String)
            type = "String";
        else
            type = "Symbol";
        return tabs + type + " (" + ((TokenNode*) &ast)->getName() + ")\n";
    }

    //    if (!ast.children.empty()) {
    //        output = tabs + "Node (" + ast.token.token + ")\n";
    //    } else {
    //        std::string type;
    //        if (ast.token.type == Token::Number)
    //            type = "Number";
    //        else if (ast.token.type == Token::String)
    //            type = "String";
    //        else
    //            type = "Symbol";
    //        return tabs + type + " (" + ast.token.token + ")\n";
    //    }
    //
//        for (const auto child: ast.) {
//            output += parse_ast(*child, level + 1);
//        }

    return output;
}

void print_ast(const SyntaxTreeNode &ast) {
    std::cout << parse_ast(ast, 0);
}
