#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool trotli(std::shared_ptr<Values::Runtime>& conditional){
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

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

std::shared_ptr<Values::Runtime> Interpreter::evaluateWhenStatement(const AST::WhenStatement& node, std::shared_ptr<Runtime::Environment> &env){
    bool truu = true;
    auto enva = std::make_shared<Runtime::Environment>(env);
    std::shared_ptr<Values::Runtime> cond = this->evaluate(node.condition, env);
        std::shared_ptr<AST::ExprAST> clone = node.clone();
        AST::WhenStatement* wil = dynamic_cast<AST::WhenStatement*>(clone.get());
        std::vector<std::shared_ptr<AST::ExprAST>> thingy = wil->consequent;
        if(trotli(cond)){
            for(auto& thing : thingy){
                std::shared_ptr<Values::Runtime> val = this->evaluate(thing, enva);
                if(val != nullptr){
                    if (val->type() == "break"){
                        break;
                    }
                }
            }
        } else {}
    return std::make_shared<Values::Null>(Values::Null());
}