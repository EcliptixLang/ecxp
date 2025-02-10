#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CAssignment(std::shared_ptr<AST::ExprAST>& astNode){
	AST::AssignmentExpr* assignment = dynamic_cast<AST::AssignmentExpr*>(astNode.get());
	if(assignment->assignee->getType() != AST::Nodes::Identifier){
		std::cout << "Invalid assignment.\n";
	}

	AST::Identifier* var = dynamic_cast<AST::Identifier*>(assignment->assignee.get());
	
	code += var->name + " = ";

	this->compile(assignment->value);
}