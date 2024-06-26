#include "SyntaxTreeNode.h"
#include "bytecode/builtin_functions/AddFunction.h"
#include "bytecode/builtin_functions/AndFunction.h"
#include "bytecode/builtin_functions/DefineFunction.h"
#include "bytecode/builtin_functions/DivideFunction.h"
#include "bytecode/builtin_functions/EqualsFunction.h"
#include "bytecode/builtin_functions/Function.h"
#include "bytecode/builtin_functions/GreaterThanFunction.h"
#include "bytecode/builtin_functions/IfFunction.h"
#include "bytecode/builtin_functions/LessThanFunction.h"
#include "bytecode/builtin_functions/MultiplyFunction.h"
#include "bytecode/builtin_functions/NotFunction.h"
#include "bytecode/builtin_functions/OrFunction.h"
#include "bytecode/builtin_functions/PrintFunction.h"
#include "bytecode/builtin_functions/ReadFunction.h"
#include "bytecode/builtin_functions/SubtractFunction.h"
#include "exceptions/SyntaxError.h"

void TokenNode::compile(
        Bytecode::Segment *segment,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    switch (token.type) {
        case Token::Number:
        case Token::String:
        case Token::Boolean:
            instructions.push_back(new (Bytecode::Instruction){
                    Bytecode::Instruction::LoadLiteral,
                    {.i_param = {Bytecode::StackObject(token)}},
            });
            break;
        case Token::Symbol:
            if (program.find_constant(token.token) != nullptr) {
                instructions.push_back(new (Bytecode::Instruction){
                        Bytecode::Instruction::LoadLiteral,
                        {.i_param = {*program.find_constant(token.token)}},
                });
            } else if (segment->find_variable(token.token) != -1) {
                instructions.push_back(new (Bytecode::Instruction){
                        Bytecode::Instruction::LoadLocal,
                        {.r_param = {segment->find_variable(token.token)}},
                });
            } else if (program.find_global(token.token) != -1) {
                instructions.push_back(new (Bytecode::Instruction){
                        Bytecode::Instruction::LoadGlobal,
                        {.r_param = {program.find_global(token.token)}},
                });
            } else {
                throw SyntaxError(
                        "Undefined variable -> " + token.token,
                        token.line,
                        token.column);
            }
        default:
            break;
    }
}

bool TokenNode::operator==(const SyntaxTreeNode &op) const {
    return type == op.type &&
           ((TokenNode *) &op)->token == token;
}

void Expression::compile(
        Bytecode::Segment *segment,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    static std::unordered_map<std::string, Bytecode::BuiltinFunctions::Function *> builtin_instructions = {
            {"+", new Bytecode::BuiltinFunctions::Add},
            {"*", new Bytecode::BuiltinFunctions::Multiply},
            {"/", new Bytecode::BuiltinFunctions::Divide},
            {"-", new Bytecode::BuiltinFunctions::Subtract},
            {"=", new Bytecode::BuiltinFunctions::Equals},
            {"<", new Bytecode::BuiltinFunctions::LessThan},
            {">", new Bytecode::BuiltinFunctions::GreaterThan},
            {"define", new Bytecode::BuiltinFunctions::Define},
            {"if", new Bytecode::BuiltinFunctions::If},
            {"print", new Bytecode::BuiltinFunctions::Print},
            {"read", new Bytecode::BuiltinFunctions::Read},
            {"not", new Bytecode::BuiltinFunctions::Not},
            {"or", new Bytecode::BuiltinFunctions::Or},
            {"and", new Bytecode::BuiltinFunctions::And}};

    if (program.find_global(function.token) != -1) {
        for (const auto &argument: args)
            argument->compile(segment, program, instructions);
        instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::LoadGlobal,
                {.r_param = {program.find_global(function.token)}},
        });
        instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::CallLambda,
                {.r_param = {args.size()}},
        });
        return;
    } else if (segment->find_variable(function.token) != -1) {
        for (const auto &argument: args)
            argument->compile(segment, program, instructions);
        instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::LoadLocal,
                {.r_param = {segment->find_variable(function.token)}},
        });
        instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::CallLambda,
                {.r_param = {args.size()}},
        });
        return;
    } else if (program.find_function(function.token) != -1) {
        if (args.size() != program.segments[program.find_function(function.token)]->variables_table.size())
            throw SyntaxError(
                    "Invalid number of arguments for function \"" + function.token +
                            "\", Expected " + std::to_string(program.segments[program.find_function(function.token)]->variables_table.size()) +
                            ", got " + std::to_string(args.size()),
                    function.line,
                    function.column);
        for (const auto &argument: args)
            argument->compile(segment, program, instructions);
        const auto called_segment = program.find_function(function.token);
        const auto arguments = program.segments[called_segment]->variables_table.size();
        instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::Call,
                {.ri_params = {called_segment, Bytecode::StackObject(arguments)}},
        });
        return;
    } else if (builtin_instructions.find(function.token) != builtin_instructions.end()) {
        builtin_instructions[function.token]->compile(
                args,
                program,
                instructions,
                segment);
    } else {
        throw SyntaxError(
                "Undefined function -> " + function.token,
                function.line,
                function.column);
    }
}

bool Expression::operator==(const SyntaxTreeNode &op) const {
    if (type != op.type || ((Expression *) &op)->function != function ||
        ((Expression *) &op)->args.size() != args.size())
        return false;

    for (auto i = 0; i < args.size(); i++) {
        if (!(*args[i] == *((Expression *) &op)->args[i]))
            return false;
    }

    return true;
}

void CondExpression::compile(
        Bytecode::Segment *result,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    typedef std::vector<Bytecode::Instruction *> fresh_instructions;
    std::vector<fresh_instructions> conditions_instructions;
    std::vector<fresh_instructions> cond_success_instructions;
    fresh_instructions default_case_instructions;

    for (const auto current_case: cases) {
        fresh_instructions condition;
        fresh_instructions condition_success;
        current_case.condition->compile(result, program, condition);
        current_case.result->compile(result, program, condition_success);
        conditions_instructions.push_back(condition);
        cond_success_instructions.push_back(condition_success);
    }

    if (default_case != nullptr) {
        default_case->compile(result, program, default_case_instructions);
    }

    size_t end = instructions.size() +
                 default_case_instructions.size() -
                 default_case_instructions.empty();
    for (size_t i = 0; i < conditions_instructions.size(); i++) {
        end += conditions_instructions[i].size();
        end += cond_success_instructions[i].size();
        end += 2;
    }

    for (size_t i = 0; i < conditions_instructions.size(); i++) {
        for (const auto instruction: conditions_instructions[i])
            result->instructions.push_back(instruction);
        result->instructions.push_back(new (Bytecode::Instruction){
                Bytecode::Instruction::CondJumpIfNot,
                {.r_param = {result->instructions.size() +
                             cond_success_instructions[i].size() +
                             2 - default_case_instructions.empty()}},
        });

        for (const auto instruction: cond_success_instructions[i])
            result->instructions.push_back(instruction);

        if (!default_case_instructions.empty())
            result->instructions.push_back(new (Bytecode::Instruction){
                    Bytecode::Instruction::Jump,
                    {.r_param = {end}},
            });
    }

    for (const auto instruction: default_case_instructions)
        result->instructions.push_back(instruction);
}

bool CondExpression::operator==(const SyntaxTreeNode &op) const {
    if (auto other = dynamic_cast<const CondExpression *>(&op)) {
        if (type != other->type || cases.size() != other->cases.size())
            return false;
        for (auto i = 0; i < cases.size(); i++)
            if (!(*cases[i].condition == *other->cases[i].condition) ||
                !(*cases[i].result == *other->cases[i].result))
                return false;
        if ((default_case == nullptr) != (other->default_case == nullptr))
            return false;
        if (default_case && other->default_case)
            return *default_case == *other->default_case;
        return true;
    }
    return false;
}

LambdaExpression::LambdaExpression(
        std::vector<SyntaxTreeNode *> args,
        SyntaxTreeNode *definition) : args(std::move(args)), definition(definition) {
    type = Type::LambdaExpression;
}

bool LambdaExpression::operator==(const SyntaxTreeNode &op) const {
    if (auto other = dynamic_cast<const LambdaExpression *>(&op)) {
        if (type != other->type || args.size() != other->args.size())
            return false;
        for (auto i = 0; i < args.size(); i++)
            if (!(*args[i] == *other->args[i]))
                return false;
        return *definition == *other->definition;
    }
    return false;
}

void LambdaExpression::compile(
        Bytecode::Segment *result,
        Bytecode::Program &program,
        std::vector<Bytecode::Instruction *> &instructions) {
    auto segment = new Bytecode::Segment({});
    size_t reg = program.declare_lambda(segment);
    for (auto argument: args)
        segment->declare_variable(((class TokenNode *) argument)->getName());
    definition->compile(segment, program, segment->instructions);
    segment->instructions.push_back(new (Bytecode::Instruction){
            Bytecode::Instruction::Return,
    });
    instructions.push_back(new (Bytecode::Instruction){
            Bytecode::Instruction::LoadLiteral,
            {.i_param = {Bytecode::StackObject(reg)}},
    });
}