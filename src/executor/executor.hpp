#pragma once

#include "../values.hpp"
#include "../ast.hpp"
#include "../utilities/env.hpp"
#include <memory>
#include <stdexcept>
#include <functional>

class InterpreterError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class Interpreter
{
public:
    std::unique_ptr<Values::Runtime> evaluate(
        const std::shared_ptr<AST::ExprAST> &astNode,
        Environment& env);

private:
    class EvalVisitor : public AST::Visitor
    {
    public:
        EvalVisitor(Interpreter &interpreter, Environment& env)
            : interpreter(interpreter), env(env) {}

        void visit(const AST::NumberLiteral &node) override
        {
            result = interpreter.evaluateNumberLiteral(node);
        }

        void visit(const AST::StringLiteral &node) override
        {
            result = interpreter.evaluateStringLiteral(node);
        }

        void visit(const AST::IdentifierExpr &node) override
        {
            result = interpreter.evaluateIdentifier(node, env);
        }

        void visit(const AST::BinaryOperationExpr &node) override
        {
            result = interpreter.evaluateBinaryOperation(node, env);
        }

        void visit(const AST::FunctionCallExpr &node) override
        {
            result = interpreter.evaluateFunctionCall(node, env);
        }

        void visit(const AST::IfStatement &node) override
        {
            result = interpreter.evaluateIfStatement(node, env);
        }

        void visit(const AST::FunctionDeclaration &node) override
        {
            result = interpreter.evaluateFunctionDeclaration(node, env);
        }

        void visit(const AST::ObjectLiteral &node) override
        {
            result = interpreter.evaluateObjectLiteral(node, env);
        }

        void visit(const AST::ImportStatement &node) override
        {
            // TODO: ADD ENVALUATE IMPORT STATEEMENT FUNCTION
        }

        void visit(const AST::WhenStatement &node) override
        {
            result = interpreter.evaluateWhenStatement(node, env);
        }

        void visit(const AST::ShellCommandExpr &node) override
        {
            result = interpreter.evaluateDSN(node, env);
        }

        void visit(const AST::VariableDeclarationExpr &node) override
        {
            result = interpreter.evaluateVariableDeclaration(node, env);
        }

        void visit(const AST::ObjectProperty &node) override
        {
            // TODO: ADD ENVALUATE OBJ PROP FUNCTION
        }

        void visit(const AST::EqualityCheckExpr &node) override
        {
            result = interpreter.evaluateEqualityExpression(node, env);
        }

        void visit(const AST::ReturnStatement &node) override
        {
        }

        void visit(const AST::ArrayLiteral &node) override
        {
            result = interpreter.evaluateArrayLiteral(node, env);
        }

        void visit(const AST::BreakStatement &node) override
        {
        }

        void visit(const AST::MemberAccessExpr &node) override
        {
            result = interpreter.evaluateMemberAccess(node, env);
        }

        void visit(const AST::WhileLoop &node) override
        {
            result = interpreter.evaluateWhileLoop(node, env);
        }

        void visit(const AST::AssignmentExpr &node) override
        {
            result = interpreter.evaluateAssignment(node, env);
        }

        void visit(const AST::ProgramRoot &node) override
        {
            result = interpreter.evaluateProgramRoot(node, env);
        }

        void visit(const AST::SkipStatement &node) override
        {
        }

        std::unique_ptr<Values::Runtime> result;
        Interpreter &interpreter;
        Environment& env;
    };

    std::unique_ptr<Values::Runtime> evaluateNumberLiteral(const AST::NumberLiteral &node);
    std::unique_ptr<Values::Runtime> evaluateStringLiteral(const AST::StringLiteral &node);
    std::unique_ptr<Values::Runtime> evaluateIdentifier(const AST::IdentifierExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateDSN(const AST::ShellCommandExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateBinaryOperation(const AST::BinaryOperationExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateFunctionCall(const AST::FunctionCallExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateIfStatement(const AST::IfStatement &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateFunctionDeclaration(const AST::FunctionDeclaration &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateObjectLiteral(const AST::ObjectLiteral &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateArrayLiteral(const AST::ArrayLiteral &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateMemberAccess(const AST::MemberAccessExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateWhileLoop(const AST::WhileLoop &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateWhenStatement(const AST::WhenStatement &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateAssignment(const AST::AssignmentExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateProgramRoot(const AST::ProgramRoot &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateEqualityExpression(const AST::EqualityCheckExpr &node, Environment& env);
    std::unique_ptr<Values::Runtime> evaluateVariableDeclaration(const AST::VariableDeclarationExpr &node, Environment& env);

    template <typename T>
    const T &verifyNode(const std::shared_ptr<AST::ExprAST> &node) const
    {
        auto ptr = static_cast<const T *>(node.get());
        if (!ptr)
        {
            throw InterpreterError("Invalid AST node type");
        }
        return *ptr;
    }

    std::unique_ptr<Values::Runtime> evaluateChild(
        const std::shared_ptr<AST::ExprAST> &node,
        Environment& env)
    {
        return evaluate(node, env);
    }

#ifdef INTERPRETER_DEBUG
    void logEvaluation(const std::string &nodeType) const
    {
        std::cerr << "Evaluating: " << nodeType << "\n";
    }
#endif
};