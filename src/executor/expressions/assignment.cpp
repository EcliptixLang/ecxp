#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateAssignment(const AST::AssignmentExpr& node, std::shared_ptr<Runtime::Environment> &env){
	if(node.target->nodeType() != AST::NodeType::IdentifierExpr){
		std::cout << "\033[31mInterpreter Error\033[0m: \033[36mInvalid Assignment\033[0m" << std::endl;
	}
	AST::IdentifierExpr* var = dynamic_cast<AST::IdentifierExpr*>(node.target.get());
	
	Runtime::Variable vall = env->get(var->name);
	if(vall.value != nullptr){
		std::shared_ptr<Values::Runtime> val = this->evaluate(node.value, env); 
		if(vall.value->type() == val->type()){
			env->set(var->name, val, vall.is_constant);
			return std::make_shared<Values::Null>(Values::Null());
		} else {
			std::cout << "\033[31mTypeError\033[0m: \033[36m" << "Assigning '" << var->name << "' with type '" << val->type() << "' is impossible\033[0m.";
			exit(6);
		}
	} else {
		return std::make_shared<Values::Null>(Values::Null());
	}
}