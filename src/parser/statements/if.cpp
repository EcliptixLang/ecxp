#include "../parser.hpp"

PAST Parser::parseIf() {
		Token token = this->expectToken(TokenType::If);
		PAST conditional = 
			this->ParseExpression();
		std::vector<PAST> consequent{};
		TokenType _operator = 
			TokenType::BinaryEquals;

		this->expectToken(TokenType::OpenBrace);

		while(
			this->NotEOF() &&
			this->currentToken().type 
				!= TokenType::CloseBrace
		){
			consequent.push_back(this->ParseStatement());
		}

		this->expectToken(TokenType::CloseBrace);
		
		std::vector<PAST> alternate{};

		if(this->currentToken().type == TokenType::Else){
			this->nextToken();
			if(this->currentToken().type == TokenType::If){
        		alternate.push_back(this->parseIf());
			} else {
				this->expectToken(TokenType::OpenBrace);

				while(
					this->NotEOF() &&
					this->currentToken().type 
						!= TokenType::CloseBrace
				){
					alternate.push_back(this->ParseStatement());
				}

				this->expectToken(TokenType::CloseBrace);
			}
		}

	return std::make_shared<AST::IfStatement>(conditional, _operator, consequent, alternate);
}