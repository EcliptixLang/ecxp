#include "../parser.hpp"

PAST Parser::ParseAdditiveExpression(){
	PAST left = this->ParseMultiplicativeExpression();
	std::shared_ptr<AST::BinaryOperationExpr> expr;
	while(this->currentToken().value == "+" || this->currentToken().value == "-"){
		std::string _operator = this->nextToken().value;
  		PAST right = this->ParseMultiplicativeExpression();
		expr = std::make_shared<AST::BinaryOperationExpr>(_operator.c_str()[0], left, right);
		left = expr;
	}
	return left;
}