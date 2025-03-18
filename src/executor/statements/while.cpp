#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool troti(std::shared_ptr<Values::Runtime>& conditional){
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

std::shared_ptr<Values::Runtime> Interpreter::evaluateWhileLoop(const AST::WhileLoop& node, std::shared_ptr<Runtime::Environment> &env){
    bool truu = true;
    while(truu){
        auto enva = std::make_shared<Runtime::Environment>(env);
        std::shared_ptr<Values::Runtime> cond = this->evaluate(node.condition, env);
        std::vector<std::shared_ptr<AST::ExprAST>> thingy = node.body;
        if(troti(cond)){
            for(auto& thing : thingy){
                std::shared_ptr<Values::Runtime> val = this->evaluate(thing, enva);
                if(val != nullptr){
                    if (val->type() == "break"){
                        break;
                    }
                }
            }
        } else {
            truu = false;
        }
    }
    return std::make_shared<Values::Null>(Values::Null());
}