#include "Compiler.h"
#include "bytecode/builtin_functions/AddFunction.h"
#include "bytecode/builtin_functions/CondFunction.h"
#include "bytecode/builtin_functions/DefineFunction.h"
#include "bytecode/builtin_functions/DivideFunction.h"
#include "bytecode/builtin_functions/EqualsFunction.h"
#include "bytecode/builtin_functions/Function.h"
#include "bytecode/builtin_functions/GreaterThanFunction.h"
#include "bytecode/builtin_functions/IfFunction.h"
#include "bytecode/builtin_functions/LessThanFunction.h"
#include "bytecode/builtin_functions/MultiplyFunction.h"
#include "bytecode/builtin_functions/PrintFunction.h"
#include "bytecode/builtin_functions/SubtractFunction.h"
#include "bytecode/instructions/Call.h"
#include "bytecode/instructions/Load.h"
#include "bytecode/instructions/LoadLiteral.h"
#include "bytecode/objects/StringLiteral.h"

namespace Bytecode {
    static std::unordered_map<std::string, BuiltinFunctions::Function *> builtin_instructions = {
            {"+", new BuiltinFunctions::Add},
            {"*", new BuiltinFunctions::Multiply},
            {"/", new BuiltinFunctions::Divide},
            {"-", new BuiltinFunctions::Subtract},
            {"=", new BuiltinFunctions::Equals},
            {"<", new BuiltinFunctions::LessThan},
            {">", new BuiltinFunctions::GreaterThan},
            {"define", new BuiltinFunctions::Define},
            {"if", new BuiltinFunctions::If},
            {"cond", new BuiltinFunctions::Cond},
            {"print", new BuiltinFunctions::Print},
    };

    void Compiler::compile(const SyntaxTreeNode &tree) {
        Compiler::compile(tree, program.segments[0]);
    }

    void Compiler::compile(const SyntaxTreeNode &tree, Segment *segment) {
        Compiler::compile(tree, segment, segment->instructions);
    }

    void Compiler::compile(const SyntaxTreeNode &tree,
                           Segment *segment,
                           std::vector<Instruction *> &instructions) {
        switch (tree.token->type) {
            case Token::Integer:
                instructions.push_back(new LoadLiteral(tree.token->asInteger()));
                break;
            case Token::Decimal:
                instructions.push_back(
                        new LoadLiteral(
                                new DecimalNumberLiteral(tree.token->asDecimal())));
                break;
            case Token::String:
                instructions.push_back(
                        new LoadLiteral(new StringLiteral(*tree.token->asString())));
                break;
            case Token::Symbol:
                if (tree.children.empty()) {
                    if (segment->find_variable(*tree.token->token) != nullptr) {
                        instructions.push_back(new Load(segment->find_variable(*tree.token->asString())));
                        return;
                    }
                    if (program.find_global(*tree.token->token) != nullptr) {
                        instructions.push_back(new Load(program.find_global(*tree.token->asString())));
                        return;
                    }
                } else {
                    if (program.find_function(*tree.token->token) != -1) {
                        for (const auto &argument: tree.children)
                            compile(*argument, segment, instructions);
                        auto called_segment = program.find_function(*tree.token->asString());
                        auto args = program.segments[called_segment]->variables_table.size();
                        instructions.push_back(new Call(called_segment, args));
                        return;
                    }
                }

                if (builtin_instructions.find(*tree.token->token) != builtin_instructions.end()) {
                    builtin_instructions[*tree.token->token]->compile(
                            tree.children,
                            *this,
                            instructions,
                            segment);
                }
                break;
            default:
                break;
        }
    }
}// namespace Bytecode