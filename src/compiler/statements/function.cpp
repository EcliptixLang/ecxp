#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CFunction(std::shared_ptr<AST::ExprAST>& astNode){
	AST::Function* fun = dynamic_cast<AST::Function*>(astNode.get());
	code += "function " + fun->name + "(";
	for(auto& param: fun->params){
		code += param + ",";
	}
	code[code.length()-1] = ')';
	code += " {\n";
	indent++;

	for(auto& val : fun->body){
		for(int i = 0; indent > i; i++){
			code += "\t";
		}
		compile(val);
		code += "\n";
	}

	code += "}";
	indent--;
}