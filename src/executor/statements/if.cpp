#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool truthy(std::unique_ptr<Values::Runtime>& conditional){
	if(conditional->type() == Values::Type::Boolean){
		Values::Boolean* cond = static_cast<Values::Boolean*>(conditional.get());
		const bool boolean = cond->value();
		if(boolean) return true; 
		else return false;
	}

	if(conditional){
		return true;
	} else {
		return false;
	}
}

std::unique_ptr<Values::Runtime> Interpreter::evaluateIfStatement(const AST::IfStatement& node, Environment& env){
	std::unique_ptr<Values::Runtime> val;
	env.enter_scope();
	std::unique_ptr<Values::Runtime> cond = this->evaluate(node.condition, env);
	if(truthy(cond)){
		for(auto& thing : node.consequent){
			val = this->evaluate(thing, env);
			if(val != nullptr){
				if (val->type() == Values::Type::Skip){
					env.leave_scope();
					return std::make_unique<Values::Null>();
				}
			}
		}
		env.leave_scope();
	} else {
		if(node.alternate.size() > 0){
			for(auto& thing : node.alternate){
				val = this->evaluate(thing, env);
				if(val != nullptr){
					if (val->type() == Values::Type::Skip){
						env.leave_scope();
						return std::make_unique<Values::Null>();	
					}
				}
			}
			env.leave_scope();
		}
	}
	return std::make_unique<Values::Null>();
}