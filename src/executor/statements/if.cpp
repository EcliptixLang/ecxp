#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool truthy(std::shared_ptr<Values::Runtime>& conditional){
	if(conditional->type() == "boolean"){
		Values::Boolean* cond = dynamic_cast<Values::Boolean*>(conditional.get());
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

std::shared_ptr<Values::Runtime> Interpreter::evaluateIfStatement(const AST::IfStatement& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> val;
	auto enva = std::make_shared<Runtime::Environment>(env);
	std::shared_ptr<Values::Runtime> cond = this->evaluate(node.condition, enva);
	if(truthy(cond)){
		for(auto& thing : node.consequent){
			val = this->evaluate(thing, enva);
			if(val != nullptr){
				if (val->type() == "skip"){
					break;	
				}
			}
		}
	} else {
		if(node.alternate.size() > 0){
			for(auto& thing : node.alternate){
				val = this->evaluate(thing, enva);
				if(val != nullptr){
					if (val->type() == "skip"){
						break;	
					}
				}
			}
		}
	}
	return std::make_shared<Values::Null>(Values::Null());
}