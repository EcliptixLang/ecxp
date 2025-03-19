#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool isTruthy(std::shared_ptr<Values::Runtime>& left, Token op, std::shared_ptr<Values::Runtime>& right){
	std::string oap = op.value;
	if(oap == "=="){
		return left->stringValue() == right->stringValue();
	} else if(oap == "!="){
		return left->stringValue() != right->stringValue();	
	} else if(oap == ">="){
		if(left->type() == "int" && right->type() == "int"){
			int l = dynamic_cast<Values::Number*>(left.get())->value();
			int r = dynamic_cast<Values::Number*>(right.get())->value();
			return l >= r;
		} else if (left->type() == "null" || right->type() == "null"){
			return false;
		} else {
			return false;
		}
	} else if(oap == "<="){
		if(left->type() == "int" && right->type() == "int"){
			int l = dynamic_cast<Values::Number*>(left.get())->value();
			int r = dynamic_cast<Values::Number*>(right.get())->value();
			return l <= r;
		} else if (left->type() == "null" || right->type() == "null"){
			return false;
		} else {
			return false;
		}
	} else if(oap == "@="){
		if(left->type() == "array"){
			std::vector<std::shared_ptr<Values::Runtime>> l = dynamic_cast<Values::Array*>(left.get())->elements();
			for(auto& lol : l){
				if(lol->stringValue() == right->stringValue())
					return true;
			}
			return false;
		} else {
			return false;
		}
	} else if(oap == "<"){
		if(left->type() == "int" && right->type() == "int"){
			int l = dynamic_cast<Values::Number*>(left.get())->value();
			int r = dynamic_cast<Values::Number*>(right.get())->value();
			return l < r;
		} else if (left->type() == "null" || right->type() == "null"){
			return false;
		} else {
			return false;
		}
	} else if(oap == ">") {
		if(left->type() == "int" && right->type() == "int"){
			int l = dynamic_cast<Values::Number*>(left.get())->value();
			int r = dynamic_cast<Values::Number*>(right.get())->value();
			return l > r;
		} else if (left->type() == "null" || right->type() == "null"){
			return false;
		} else {
			return false;
		}
	}
	return false;
}

std::shared_ptr<Values::Runtime> Interpreter::evaluateEqualityExpression(const AST::EqualityCheckExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> left = this->evaluate(node.left, env);
	std::shared_ptr<Values::Runtime> right = this->evaluate(node.right, env);

	if(isTruthy(left, node.operatorToken, right)){
		return std::make_shared<Values::Boolean>(true);
	}
	else return std::make_shared<Values::Boolean>(false);

}