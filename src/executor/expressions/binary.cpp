#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateBinaryOperation(const AST::BinaryOperationExpr& node, Runtime::Environment& env){
	std::unique_ptr<Values::Runtime> lhs = this->evaluate(node.lhs, env);
	std::unique_ptr<Values::Runtime> rhs = this->evaluate(node.rhs, env);

	Values::Type lhsType = lhs->type();
	Values::Type rhsType = rhs->type();

	if(lhsType == Values::Type::Number && rhsType == Values::Type::Number){
		int result;
		 Values::Number* numl = static_cast<Values::Number*>(lhs.get());
		Values::Number* numr = static_cast<Values::Number*>(rhs.get());
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

		return std::make_unique<Values::Number>(Values::Number(result));

	} else if(lhsType == Values::Type::Null || rhsType == Values::Type::Null){
			return std::make_unique<Values::Null>(Values::Null());
	} else {
		string value = "";
		if((lhsType != Values::Type::Function || lhsType != Values::Type::Object) && (rhsType != Values::Type::Function || rhsType != Values::Type::Object)){
			value.append(lhs->stringValue()).append(rhs->stringValue());
		} else {
			value = "null";
		}
		return std::make_unique<Values::String>(Values::String(value));
	}

	return std::make_unique<Values::Null>();
}