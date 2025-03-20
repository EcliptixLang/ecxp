#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include "./lexer/lexer.hpp"

namespace AST {

enum class NodeType {
    NumberLiteral,
    StringLiteral,
    ProgramRoot,
    IdentifierExpr,
    VariableDeclaration,
    SkipStatement,
    AssignmentExpr,
    BinaryOperation,
    FunctionCall,
    ImportStatement,
    WhenStatement,
    WhileLoop,
    IfStatement,
    FunctionDeclaration,
    ArrayLiteral,
    ShellCommand,
    ObjectProperty, 
    ObjectLiteral, 
    MemberAccess,
    EqualityCheck,
    BreakStatement,
    NewExpression,
    ReturnStatement
};

class NumberLiteral;
class StringLiteral;
class ProgramRoot;
class IdentifierExpr;
class VariableDeclarationExpr;
class AssignmentExpr;
class BinaryOperationExpr;
class FunctionCallExpr;
class ImportStatement;
class WhenStatement;
class WhileLoop;
class IfStatement;
class FunctionDeclaration;
class ArrayLiteral;
class ShellCommandExpr;
class ObjectProperty;
class ObjectLiteral;
class MemberAccessExpr;
class EqualityCheckExpr;
class BreakStatement;
class ReturnStatement;
class SkipStatement;

    class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visit(const NumberLiteral& node) = 0;
        virtual void visit(const StringLiteral& node) = 0;
        virtual void visit(const ProgramRoot& node) = 0;
        virtual void visit(const IdentifierExpr& node) = 0;
        virtual void visit(const VariableDeclarationExpr& node) = 0;
        virtual void visit(const AssignmentExpr& node) = 0;
        virtual void visit(const BinaryOperationExpr& node) = 0;
        virtual void visit(const FunctionCallExpr& node) = 0;
        virtual void visit(const ImportStatement& node) = 0;
        virtual void visit(const WhenStatement& node) = 0;
        virtual void visit(const WhileLoop& node) = 0;
        virtual void visit(const IfStatement& node) = 0;
        virtual void visit(const FunctionDeclaration& node) = 0;
        virtual void visit(const ArrayLiteral& node) = 0;
        virtual void visit(const ShellCommandExpr& node) = 0;
        virtual void visit(const ObjectProperty& node) = 0;
        virtual void visit(const ObjectLiteral& node) = 0;
        virtual void visit(const MemberAccessExpr& node) = 0;
        virtual void visit(const EqualityCheckExpr& node) = 0;
        virtual void visit(const BreakStatement& node) = 0;
        virtual void visit(const ReturnStatement& node) = 0;
//        virtual void visit(const ClassDeclaration& node) = 0;
        virtual void visit(const SkipStatement& node) = 0;
    };

std::string nodeTypeToString(NodeType type);

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual NodeType nodeType() const = 0;
    virtual std::shared_ptr<ExprAST> clone() const = 0;
    virtual void accept(Visitor& visitor) const = 0;
};

class NumberLiteral : public ExprAST {
public:
    double value;
    
    explicit NumberLiteral(double val) : value(val) {}
    
    NodeType nodeType() const override { 
        return NodeType::NumberLiteral; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<NumberLiteral>(*this);
    }

    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class StringLiteral : public ExprAST {
public:
    std::string value;
    
    explicit StringLiteral(std::string val) : value(std::move(val)) {}
    
    NodeType nodeType() const override { 
        return NodeType::StringLiteral; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<StringLiteral>(*this);
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class ProgramRoot : public ExprAST {
public:
    std::vector<std::shared_ptr<ExprAST>> body;
    
    explicit ProgramRoot(std::vector<std::shared_ptr<ExprAST>> body) 
        : body(std::move(body)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ProgramRoot; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedBody;
        for(const auto& expr : body) {
            clonedBody.push_back(expr->clone());
        }
        return std::make_shared<ProgramRoot>(clonedBody);
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class IdentifierExpr : public ExprAST {
public:
    std::string name;
    
    explicit IdentifierExpr(std::string name) 
        : name(std::move(name)) {}
    
    NodeType nodeType() const override { 
        return NodeType::IdentifierExpr; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<IdentifierExpr>(*this);
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class VariableDeclarationExpr : public ExprAST {
public:
    std::string identifier;
    std::string typeHint;
    std::shared_ptr<ExprAST> initialValue;
    bool isConstant;
    
    VariableDeclarationExpr(std::string id, std::string type, 
                          std::shared_ptr<ExprAST> value, bool isConst)
        : identifier(std::move(id)), 
          typeHint(std::move(type)),
          initialValue(std::move(value)),
          isConstant(isConst) {}
    
    NodeType nodeType() const override { 
        return NodeType::VariableDeclaration; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<VariableDeclarationExpr>(
            identifier, typeHint, initialValue->clone(), isConstant);
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class AssignmentExpr : public ExprAST {
public:
    std::shared_ptr<ExprAST> target;
    std::shared_ptr<ExprAST> value;
    
    AssignmentExpr(std::shared_ptr<ExprAST> target, 
                 std::shared_ptr<ExprAST> value)
        : target(std::move(target)), 
          value(std::move(value)) {}
    
    NodeType nodeType() const override { 
        return NodeType::AssignmentExpr; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<AssignmentExpr>(
            target->clone(), value->clone());
    }
};

class BinaryOperationExpr : public ExprAST {
public:
    char op;
    std::shared_ptr<ExprAST> lhs;
    std::shared_ptr<ExprAST> rhs;
    
    BinaryOperationExpr(char op, std::shared_ptr<ExprAST> lhs,
                      std::shared_ptr<ExprAST> rhs)
        : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    
    NodeType nodeType() const override { 
        return NodeType::BinaryOperation; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<BinaryOperationExpr>(
            op, lhs->clone(), rhs->clone());
    }
};

class FunctionCallExpr : public ExprAST {
public:
    std::shared_ptr<ExprAST> callee;
    std::vector<std::shared_ptr<ExprAST>> arguments;
    
    FunctionCallExpr(std::shared_ptr<ExprAST> callee,
                   std::vector<std::shared_ptr<ExprAST>> args)
        : callee(std::move(callee)), 
          arguments(std::move(args)) {}
    
    NodeType nodeType() const override { 
        return NodeType::FunctionCall; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedArgs;
        for(const auto& arg : arguments) {
            clonedArgs.push_back(arg->clone());
        }
        return std::make_shared<FunctionCallExpr>(
            callee->clone(), clonedArgs);
    }
};

class ImportStatement : public ExprAST {
public:
    std::string library;
    std::vector<std::string> imports;
    
    ImportStatement(std::string lib, std::vector<std::string> items)
        : library(std::move(lib)), 
          imports(std::move(items)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ImportStatement; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<ImportStatement>(*this);
    }
};

class WhenStatement : public ExprAST {
public:
    std::shared_ptr<ExprAST> condition;
    TokenType comparisonOp;
    std::vector<std::shared_ptr<ExprAST>> consequent;
    
    WhenStatement(std::shared_ptr<ExprAST> cond, 
                TokenType opType,
                std::vector<std::shared_ptr<ExprAST>> body)
        : condition(std::move(cond)),
          comparisonOp(opType),
          consequent(std::move(body)) {}
    
    NodeType nodeType() const override { 
        return NodeType::WhenStatement; 
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedBody;
        for(const auto& expr : consequent) {
            clonedBody.push_back(expr->clone());
        }
        return std::make_shared<WhenStatement>(
            condition->clone(), comparisonOp, clonedBody);
    }
};

class WhileLoop : public ExprAST {
public:
    std::shared_ptr<ExprAST> condition;
    TokenType loopType;
    std::vector<std::shared_ptr<ExprAST>> body;
    
    WhileLoop(std::shared_ptr<ExprAST> cond, 
            TokenType opType,
            std::vector<std::shared_ptr<ExprAST>> loopBody)
        : condition(std::move(cond)),
          loopType(opType),
          body(std::move(loopBody)) {}
    
    NodeType nodeType() const override { 
        return NodeType::WhileLoop; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedBody;
        for(const auto& expr : body) {
            clonedBody.push_back(expr->clone());
        }
        return std::make_shared<WhileLoop>(
            condition->clone(), loopType, clonedBody);
    }
};

class IfStatement : public ExprAST {
public:
    std::shared_ptr<ExprAST> condition;
    TokenType conditionType;
    std::vector<std::shared_ptr<ExprAST>> consequent;
    std::vector<std::shared_ptr<ExprAST>> alternate;
    
    IfStatement(std::shared_ptr<ExprAST> cond, 
              TokenType opType,
              std::vector<std::shared_ptr<ExprAST>> thenBranch,
              std::vector<std::shared_ptr<ExprAST>> elseBranch)
        : condition(std::move(cond)),
          conditionType(opType),
          consequent(std::move(thenBranch)),
          alternate(std::move(elseBranch)) {}
    
    NodeType nodeType() const override { 
        return NodeType::IfStatement; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedConsequent;
        for(const auto& expr : consequent) {
            clonedConsequent.push_back(expr->clone());
        }
        
        std::vector<std::shared_ptr<ExprAST>> clonedAlternate;
        for(const auto& expr : alternate) {
            clonedAlternate.push_back(expr->clone());
        }
        
        return std::make_shared<IfStatement>(
            condition->clone(), conditionType, 
            clonedConsequent, clonedAlternate);
    }
};

class FunctionDeclaration : public ExprAST {
public:
    std::vector<std::string> parameters;
    std::string name;
    std::string returnType;
    std::vector<std::shared_ptr<ExprAST>> body;
    
    FunctionDeclaration(std::vector<std::string> params,
                      std::string funcName,
                      std::vector<std::shared_ptr<ExprAST>> funcBody,
                      std::string retType)
        : parameters(std::move(params)),
          name(std::move(funcName)),
          body(std::move(funcBody)),
          returnType(std::move(retType)) {}
    
    NodeType nodeType() const override { 
        return NodeType::FunctionDeclaration; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedBody;
        for(const auto& expr : body) {
            clonedBody.push_back(expr->clone());
        }
        return std::make_shared<FunctionDeclaration>(
            parameters, name, clonedBody, returnType);
    }
};

class ArrayLiteral : public ExprAST {
public:
    std::vector<std::shared_ptr<ExprAST>> elements;
    
    explicit ArrayLiteral(std::vector<std::shared_ptr<ExprAST>> elements)
        : elements(std::move(elements)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ArrayLiteral; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedElements;
        for(const auto& elem : elements) {
            clonedElements.push_back(elem->clone());
        }
        return std::make_shared<ArrayLiteral>(clonedElements);
    }
};

class ShellCommandExpr : public ExprAST {
public:
    std::string command;
    
    explicit ShellCommandExpr(std::string cmd) 
        : command(std::move(cmd)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ShellCommand; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<ShellCommandExpr>(*this);
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class ObjectProperty : public ExprAST {
public:
    std::string key;
    std::shared_ptr<ExprAST> value;
    
    ObjectProperty(std::string propKey, std::shared_ptr<ExprAST> propValue)
        : key(std::move(propKey)), 
          value(std::move(propValue)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ObjectProperty; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<ObjectProperty>(
            key, value->clone());
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class ObjectLiteral : public ExprAST {
public:
    std::vector<std::shared_ptr<ExprAST>> properties;
    
    explicit ObjectLiteral(std::vector<std::shared_ptr<ExprAST>> props)
        : properties(std::move(props)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ObjectLiteral; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        std::vector<std::shared_ptr<ExprAST>> clonedProps;
        for(const auto& prop : properties) {
            clonedProps.push_back(prop->clone());
        }
        return std::make_shared<ObjectLiteral>(clonedProps);
    }
};

class MemberAccessExpr : public ExprAST {
public:
    std::shared_ptr<ExprAST> object;
    std::shared_ptr<ExprAST> property;
    bool computed;
    
    MemberAccessExpr(std::shared_ptr<ExprAST> obj,
                   std::shared_ptr<ExprAST> prop,
                   bool isComputed)
        : object(std::move(obj)),
          property(std::move(prop)),
          computed(isComputed) {}
    
    NodeType nodeType() const override { 
        return NodeType::MemberAccess; 
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<MemberAccessExpr>(
            object->clone(), property->clone(), computed);
    }
};

class ReturnStatement : public ExprAST {
public:
    std::shared_ptr<ExprAST> returnValue;
    
    explicit ReturnStatement(std::shared_ptr<ExprAST> value)
        : returnValue(std::move(value)) {}
    
    NodeType nodeType() const override { 
        return NodeType::ReturnStatement; 
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<ReturnStatement>(
            returnValue ? returnValue->clone() : nullptr);
    }
};

class EqualityCheckExpr : public ExprAST {
public:
    std::shared_ptr<ExprAST> left;
    std::shared_ptr<ExprAST> right;
    Token operatorToken;
    
    EqualityCheckExpr(std::shared_ptr<ExprAST> lhs,
                    std::shared_ptr<ExprAST> rhs,
                    Token op)
        : left(std::move(lhs)),
          right(std::move(rhs)),
          operatorToken(std::move(op)) {}
    
    NodeType nodeType() const override { 
        return NodeType::EqualityCheck; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<EqualityCheckExpr>(
            left->clone(), right->clone(), operatorToken);
    }
};

class BreakStatement : public ExprAST {
public:
    NodeType nodeType() const override { 
        return NodeType::BreakStatement; 
    }
    
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<BreakStatement>();
    }
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
};

class SkipStatement : public ExprAST {
public:
    NodeType nodeType() const override { 
        return NodeType::SkipStatement; 
    }
    
    void accept(Visitor& visitor) const override {
      visitor.visit(*this);
    }
    std::shared_ptr<ExprAST> clone() const override {
        return std::make_shared<SkipStatement>();
    }
};
}