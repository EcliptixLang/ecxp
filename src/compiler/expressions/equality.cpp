#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CEqu(std::shared_ptr<AST::ExprAST>& astNode){
	AST::EquExpr* equ = dynamic_cast<AST::EquExpr*>(astNode.get());

	this->compile(equ->left);

	code += " " + equ->oper.value + " ";

	this->compile(equ->right);

}