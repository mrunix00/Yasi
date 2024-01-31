#include "Compiler.h"
#include "bytecode/builtin_functions/AddFunction.h"
#include "bytecode/builtin_functions/DefineFunction.h"
#include "bytecode/builtin_functions/DivideFunction.h"
#include "bytecode/builtin_functions/EqualsFunction.h"
#include "bytecode/builtin_functions/Function.h"
#include "bytecode/builtin_functions/GreaterThanFunction.h"
#include "bytecode/builtin_functions/IfFunction.h"
#include "bytecode/builtin_functions/LessThanFunction.h"
#include "bytecode/builtin_functions/MultiplyFunction.h"
#include "bytecode/builtin_functions/SubtractFunction.h"
#include "bytecode/instructions/Add.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadGlobal.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/instructions/Store.h"

namespace Bytecode {
    void Compiler::compile(
            const SyntaxTreeNode &tree,
            std::vector<Instruction *> &result) {
        std::unordered_map<std::string, BuiltinFunctions::Function *> builtin_instructions = {
                {"+", new BuiltinFunctions::Add},
                {"*", new BuiltinFunctions::Multiply},
                {"/", new BuiltinFunctions::Divide},
                {"-", new BuiltinFunctions::Subtract},
                {"=", new BuiltinFunctions::Equals},
                {"<", new BuiltinFunctions::LessThan},
                {">", new BuiltinFunctions::GreaterThan},
                {"define", new BuiltinFunctions::Define},
                {"if", new BuiltinFunctions::If},
        };

        switch (tree.token->type) {
            case Token::Integer:
                result.push_back(new LoadLiteral(tree.token->asInteger()));
                break;
            case Token::Symbol:
                if (tree.children.empty()) {
                    if (program.find_variable(*tree.token->token) != -1) {
                        result.push_back(new Load(program.find_variable(*tree.token->asString())));
                        return;
                    }
                    if (program.find_global(*tree.token->token) != -1) {
                        result.push_back(new LoadGlobal(program.find_global(*tree.token->asString())));
                        return;
                    }
                } else {
                    if (program.find_function(*tree.token->token) != -1) {
                        for (const auto &argument: tree.children)
                            compile(*argument, result);
                        result.push_back(new Call(program.find_function(*tree.token->asString())));
                        return;
                    }
                }


                if (builtin_instructions.find(*tree.token->token) != builtin_instructions.end()) {
                    builtin_instructions[*tree.token->token]->compile(
                            tree.children,
                            *this,
                            result);
                }
                break;
            default:
                break;
        }
    }

    void Compiler::compile(const SyntaxTreeNode &tree) {
        Compiler::compile(tree, program.segments[0]->instructions);
    }
}