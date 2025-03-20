#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateAssignment(const AST::AssignmentExpr& node, Environment& env){
	if(node.target->nodeType() != AST::NodeType::IdentifierExpr){
		std::cout << "\033[31mInterpreter Error\033[0m: \033[36mInvalid Assignment\033[0m" << std::endl;
	}
	AST::IdentifierExpr* var = static_cast<AST::IdentifierExpr*>(node.target.get());
	
	Values::Runtime* vall = env.get(var->name);
	if(vall){
		std::unique_ptr<Values::Runtime> val = this->evaluate(node.value, env); 
		if(vall->type() == val->type()){
			env.set(var->name, std::move(val));
			return std::make_unique<Values::Null>(Values::Null());
		} else {
			std::cout << "\033[31mTypeError\033[0m: \033[36m" << "Assigning '" << var->name << "' with type '" << val->stringType() << "' is impossible\033[0m.";
			exit(6);
		}
	} else {
		return std::make_unique<Values::Null>(Values::Null());
	}
}