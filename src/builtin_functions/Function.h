#ifndef YASI_FUNCTION_H
#define YASI_FUNCTION_H

class Function {
public:
    virtual ~Function()= default;
    virtual SyntaxTreeNode evaluate(const std::vector<SyntaxTreeNode>& args) = 0;
};

#endif
