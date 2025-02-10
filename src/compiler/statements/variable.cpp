#include "../compiler.hpp"
#include <memory>

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CVariable(std::shared_ptr<AST::ExprAST>& astNode){
	AST::VariableExpr* var = dynamic_cast<AST::VariableExpr*>(astNode.get());

	if(var->constant){
		code += "const";
	} else {
		code += "let";
	}

	code += " " + var->Name;

	code += " = ";

	compile(var->Value);
}