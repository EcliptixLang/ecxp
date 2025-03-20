#include "executor.hpp"
#include <string>
#include <stdexcept>

using NodeType = AST::NodeType;

const std::string& nodeTypeTranslate(NodeType type) {
    switch(type) {
        case NodeType::NumberLiteral:    { static std::string s = "NumberLiteral"; return s; }
        case NodeType::StringLiteral:    { static std::string s = "StringLiteral"; return s; }
        case NodeType::ProgramRoot:      { static std::string s = "ProgramRoot"; return s; }
        case NodeType::IdentifierExpr:   { static std::string s = "IdentifierExpr"; return s; }
        case NodeType::VariableDeclaration: { static std::string s = "VariableDeclaration"; return s; }
        case NodeType::SkipStatement:    { static std::string s = "SkipStatement"; return s; }
        case NodeType::AssignmentExpr:   { static std::string s = "AssignmentExpr"; return s; }
        case NodeType::BinaryOperation:  { static std::string s = "BinaryOperation"; return s; }
        case NodeType::FunctionCall:     { static std::string s = "FunctionCall"; return s; }
        case NodeType::ImportStatement:  { static std::string s = "ImportStatement"; return s; }
        case NodeType::WhenStatement:    { static std::string s = "WhenStatement"; return s; }
        case NodeType::WhileLoop:        { static std::string s = "WhileLoop"; return s; }
        case NodeType::IfStatement:      { static std::string s = "IfStatement"; return s; }
        case NodeType::FunctionDeclaration: { static std::string s = "FunctionDeclaration"; return s; }
        case NodeType::ArrayLiteral:     { static std::string s = "ArrayLiteral"; return s; }
        case NodeType::ShellCommand:     { static std::string s = "ShellCommand"; return s; }
        case NodeType::ObjectProperty:   { static std::string s = "ObjectProperty"; return s; }
        case NodeType::ObjectLiteral:    { static std::string s = "ObjectLiteral"; return s; }
        case NodeType::MemberAccess:     { static std::string s = "MemberAccess"; return s; }
        case NodeType::EqualityCheck:    { static std::string s = "EqualityCheck"; return s; }
        case NodeType::BreakStatement:   { static std::string s = "BreakStatement"; return s; }
        case NodeType::NewExpression:    { static std::string s = "NewExpression"; return s; }
        case NodeType::ReturnStatement:  { static std::string s = "ReturnStatement"; return s; }
        default:
            throw std::invalid_argument("Unknown NodeType");
    }
}

using NodeType = AST::NodeType; 
using string = std::string;

bool traoti(std::unique_ptr<Values::Runtime>& conditional){
	if(conditional->type() == Values::Type::Boolean){
		Values::Boolean* cond = static_cast<Values::Boolean*>(conditional.get());
		const bool boolean = cond->value();
		if(boolean) return true; 
		else return false;
	}

	if(conditional){
		return true;
	} else {
		return false;
	}
}

void runCommand(const string& command) {
	system(command.c_str());
}

using namespace AST;
using namespace Values;

std::unique_ptr<Values::Runtime> Interpreter::evaluate(
    const std::shared_ptr<ExprAST>& astNode,
    Runtime::Environment& env
) {
    try {
        EvalVisitor visitor(*this, env);
        astNode->accept(visitor);
        
        if (!visitor.result) {
            throw InterpreterError("Evaluation returned null result " + nodeTypeTranslate(astNode->nodeType()));
        }
        return std::move(visitor.result);
    } catch (const InterpreterError& e) {
        throw InterpreterError(std::string("Evaluation failed: ") + e.what());
    }
}