#include "../parser.hpp"

PAST Parser::parseObjects() {
		if(this->currentToken().type != TokenType::OpenBrace){
			return this->ParseAdditiveExpression();
		}

		Token token = this->nextToken();
		std::vector<PAST> map;

		while(
			this->NotEOF() && 
			this->currentToken().type 
				!= TokenType::CloseBrace
		){
			std::string key = this->expectToken(TokenType::Identifier).value;

			if (this->currentToken().type == TokenType::Comma) {
				this->nextToken(); 
				map.push_back(
					std::make_shared<AST::Element>(
						AST::Element(
							key, nullptr
						)
					)
				);
				continue;
			} 
			else if (this->currentToken().type == TokenType::CloseBrace) {
				map.push_back(
					std::make_shared<AST::Element>(
						AST::Element(
							key, nullptr
						)
					)
				);
				continue;
			}

			this->expectToken(TokenType::Colon);

			PAST value = 
				this->ParseExpression();
      		map.push_back(
				std::make_shared<AST::Element>(key, value)
			);
			if(
				this->currentToken().type != 
				TokenType::CloseBrace
			) this->expectToken(TokenType::Comma);
		}

		this->expectToken(TokenType::CloseBrace);
		return std::make_shared<AST::Object>(map);
	}