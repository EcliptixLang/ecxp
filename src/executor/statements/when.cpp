#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool trotli(std::unique_ptr<Values::Runtime>& conditional){
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

std::unique_ptr<Values::Runtime> Interpreter::evaluateWhenStatement(const AST::WhenStatement& node, Environment& env){
    return std::make_unique<Values::Null>();
}