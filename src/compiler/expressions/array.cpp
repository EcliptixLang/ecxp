#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CArray(std::shared_ptr<AST::ExprAST>& astNode){
	AST::Array* arr = dynamic_cast<AST::Array*>(astNode.get());

	code += "[";

	for(auto& val : arr->elements){
		this->compile(val);
		code += ", ";
	}

	code += "]";
}
