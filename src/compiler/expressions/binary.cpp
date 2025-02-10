#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CBinary(std::shared_ptr<AST::ExprAST>& astNode){
	AST::BinaryExpr* binexp = dynamic_cast<AST::BinaryExpr*>(astNode.get());

	this->compile(binexp->LHS);

	code += " " + binexp->Op;
	code += " ";

	this->compile(binexp->RHS);

}