#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CIf(std::shared_ptr<AST::ExprAST>& astNode){
	AST::IfStatement* if_ = dynamic_cast<AST::IfStatement*>(astNode.get());
	
	code += "if (";
	this->compile(if_->conditional);
	code += ") {";
	indent++;
	code += "\n";
	
	for(auto& thing : if_->consequent){
		for(int i = 0; indent > i; i++){
			code += "\t";
		}
		this->compile(thing);
		code += "\n";
	}
	indent--;
	code += "}";
		
	if(if_->alternate.size() > 0){
		code += " else {";
		indent++;
		for(auto& thing : if_->alternate){
			this->compile(thing);
		}

		indent--;
		code += "}";
	}

}