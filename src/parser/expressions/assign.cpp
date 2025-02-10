#include "../parser.hpp"

PAST Parser::parseAssignment() {
		PAST left = this->parseArrays();

		if(this->currentToken().type == TokenType::Equals){
			Token token = this->nextToken();
			PAST value =
				this->parseAssignment();

			return std::make_shared<AST::AssignmentExpr>(left, value);
		}

		return left;
	}