#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CCall(std::shared_ptr<AST::ExprAST>& astNode){
	AST::CallExpr* call = dynamic_cast<AST::CallExpr*>(astNode.get());
	
	this->compile(call->Callee);

	code += "(";

	for(auto& arg : call->Args){
		this->compile(arg);
		
		if(call->Args[call->Args.size()-1] != arg)
			code += ", ";
	}

	code += ")";
}