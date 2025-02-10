#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CNumber(std::shared_ptr<AST::ExprAST>& astNode){
	AST::NumberExpr* number = dynamic_cast<AST::NumberExpr*>(astNode.get());
	code += number->Value;
}