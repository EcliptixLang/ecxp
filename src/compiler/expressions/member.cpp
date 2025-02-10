#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CMember(std::shared_ptr<AST::ExprAST>& astNode){
	AST::MemberExpr* mem = dynamic_cast<AST::MemberExpr*>(astNode.get());

	this->compile(mem->object);

	code += ".";

	AST::Identifier* id = dynamic_cast<AST::Identifier*>(mem->property.get());
	code += id->name;

}