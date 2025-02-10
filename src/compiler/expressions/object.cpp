#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CObject(std::shared_ptr<AST::ExprAST>& astNode){
	AST::Object* obj = dynamic_cast<AST::Object*>(astNode.get());
	
	code += "{";
	indent++;

	for (const auto& val : obj->map) {
		AST::Element* element = dynamic_cast<AST::Element*>(val.get());
		code += element->key;
		code += ": ";
	 	this->compile(element->value);
		code += ",\n";
	}

	indent--;
	code += "}";
}