#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CIdent(std::shared_ptr<AST::ExprAST>& astNode){
	AST::Identifier * ident = dynamic_cast<AST::Identifier*>(astNode.get());
	
	code += ident->name;
}