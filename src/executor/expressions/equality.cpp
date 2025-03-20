#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool isTruthy(std::unique_ptr<Values::Runtime>& left, Token op, std::unique_ptr<Values::Runtime>& right){
	std::string oap = op.value;
	if(oap == "=="){
		return left->stringValue() == right->stringValue();
	} else if(oap == "!="){
		return left->stringValue() != right->stringValue();	
	} else if(oap == ">="){
		if(left->type() == Values::Type::Number && right->type() == Values::Type::Number){
			int l = static_cast<Values::Number*>(left.get())->value();
			int r = static_cast<Values::Number*>(right.get())->value();
			return l >= r;
		} else if (left->type() == Values::Type::Null || right->type() == Values::Type::Null){
			return false;
		} else {
			return false;
		}
	} else if(oap == "<="){
		if(left->type() == Values::Type::Number && right->type() == Values::Type::Number){
			int l = static_cast<Values::Number*>(left.get())->value();
			int r = static_cast<Values::Number*>(right.get())->value();
			return l <= r;
		} else if (left->type() == Values::Type::Null || right->type() == Values::Type::Null){
			return false;
		} else {
			return false;
		}
	} /*else if(oap == "@="){
		if(left->type() == Values::Type::Array){
			Values::Array* arr = static_cast<Values::Array*>(left.get());
			std::vector<std::unique_ptr<Values::Runtime>> l = arr->elements();
			for(auto& lol : l){
				if(lol->type() != right->type()) continue;
				if(lol->stringValue() == right->stringValue())
					return true;
			}
			return false;
		} else {
			return false;
		}
	}*/ else if(oap == "<"){
		if(left->type() == Values::Type::Number && right->type() == Values::Type::Number){
			int l = static_cast<Values::Number*>(left.get())->value();
			int r = static_cast<Values::Number*>(right.get())->value();
			return l < r;
		} else if (left->type() == Values::Type::Null || right->type() == Values::Type::Null){
			return false;
		} else {
			return false;
		}
	} else if(oap == ">") {
		if(left->type() == Values::Type::Number && right->type() == Values::Type::Number){
			int l = static_cast<Values::Number*>(left.get())->value();
			int r = static_cast<Values::Number*>(right.get())->value();
			return l > r;
		} else if (left->type() == Values::Type::Null || right->type() == Values::Type::Null){
			return false;
		} else {
			return false;
		}
	}
	return false;
}

std::unique_ptr<Values::Runtime> Interpreter::evaluateEqualityExpression(const AST::EqualityCheckExpr& node, Runtime::Environment& env){
	std::unique_ptr<Values::Runtime> left = this->evaluate(node.left, env);
	std::unique_ptr<Values::Runtime> right = this->evaluate(node.right, env);

	if(isTruthy(left, node.operatorToken, right)){
		return std::make_unique<Values::Boolean>(true);
	}
	else return std::make_unique<Values::Boolean>(false);

}