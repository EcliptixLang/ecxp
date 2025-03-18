#include "../parser.hpp"

PAST Parser::parseWhen() {
		this->expectToken(TokenType::When);
		PAST conditional = this->ParseExpression();
		std::vector<PAST> consequent{};
		TokenType _operator = TokenType::BinaryEquals;

		this->expectToken(TokenType::OpenBrace);
		Token token = this->currentToken();

		while(this->NotEOF() && this->Tokens[pos].type != TokenType::CloseBrace){
			consequent.push_back(this->ParseStatement());
		}

		this->expectToken(TokenType::CloseBrace);

		return std::make_shared<AST::WhenStatement>(conditional, _operator, consequent);
	}