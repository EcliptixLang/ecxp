#include "../parser.hpp"

PAST Parser::parseMember() {
	PAST object = this->ParsePrimary();
	while(this->currentToken().type == TokenType::Dot || this->currentToken().type == TokenType::OpenBracket){
		Token _operator = this->nextToken();
		PAST property;
		bool computed;

		if(_operator.type == TokenType::Dot){
			computed = false;
			property = this->ParsePrimary();
			if(property->nodeType() != AST::NodeType::IdentifierExpr){
				throw std::runtime_error("idk");
			}
		} else {
			computed = true;
			property = this->ParseExpression();
			this->expectToken(TokenType::CloseBracket);
		}

		object = std::make_shared<AST::MemberAccessExpr>(object, property, computed);
	}

	return object;
}