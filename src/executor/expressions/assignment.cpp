#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateAssignment(const AST::AssignmentExpr& node, std::shared_ptr<Runtime::Environment> &env){
	if(node.target->nodeType() != AST::NodeType::IdentifierExpr){
		std::cout << "Invalid assignment.\n";
	}
	AST::IdentifierExpr* var = dynamic_cast<AST::IdentifierExpr*>(node.target.get());
	
	Runtime::Variable vall = env->get(var->name);
	if(vall.value != nullptr){
		std::shared_ptr<Values::Runtime> val = this->evaluate(node.value, env); 
		if(vall.value->type() == val->type()){
			env->set(var->name, val, vall.is_constant);
			return std::make_shared<Values::Null>(Values::Null());
		} else {
			std::cout << "Error while declaring variable '" << var->name << "', because it seems like it's requiring type '" << vall.value->type() << "' and the value applied to it was of type '" << val->type() << "'.\n";
			exit(6);
		}
	} else {
		return std::make_shared<Values::Null>(Values::Null());
	}
}