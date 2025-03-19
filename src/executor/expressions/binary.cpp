#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateBinaryOperation(const AST::BinaryOperationExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> lhs = this->evaluate(node.lhs, env);
	std::shared_ptr<Values::Runtime> rhs = this->evaluate(node.rhs, env);

	string lhsType = lhs->type();
	string rhsType = rhs->type();

	if(lhs->type() == "int" && rhs->type() == "int"){
		int result;
		 Values::Number* numl = dynamic_cast<Values::Number*>(lhs.get());
		Values::Number* numr = dynamic_cast<Values::Number*>(rhs.get());
		if(node.op == '+'){
			result = numl->value() + numr->value();
		} else if(node.op == '-'){
			result = numl->value() - numr->value();
		} else if(node.op == '*'){
			result = numl->value() * numr->value();
		} else if(node.op == '/'){
			result = numl->value() / numr->value();
		} else {
			std::cout << "Unknown expression: " << numl->value() << " " << node.op << " " << numr->value() << "\n"; 
		}

		return std::make_shared<Values::Number>(Values::Number(result));

	} else if(lhs->type() == "null" || lhs->type() == "null"){
			return std::make_shared<Values::Null>(Values::Null());
	} else {
		string lhsType = lhs->type();
		string rhsType = rhs->type();
		string value = "";
		if((lhsType != "function" || lhsType != "Object") && (rhsType != "function" || rhsType != "Object")){
			value.append(lhs->stringValue()).append(rhs->stringValue());
		} else {
			value = "null";
		}
		return std::make_shared<Values::String>(Values::String(value));
	}

	return std::make_shared<Values::Null>(Values::Null());
}