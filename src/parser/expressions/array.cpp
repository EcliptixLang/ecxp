#include "../parser.hpp"

PAST Parser::parseArrays() {
		Token nex = this->currentToken();
		if(nex.type != TokenType::OpenBracket){
			return this->parseDSNotation();
		}

		this->nextToken();

		int num = -1;
		std::vector<PAST> arr{};

		while(this->NotEOF() && this->currentToken().type != TokenType::CloseBracket) {
			PAST key = 
				this->ParseExpression();
			num++;
			TokenType ttype = this->nextToken().type;
			if(
				ttype == TokenType::Comma || 
				ttype == TokenType::CloseBracket
			){
				arr.push_back(key);
				continue;
			}

			if(ttype != TokenType::CloseBracket){
				if(
					this->currentToken().type == 
					TokenType::Comma
				) throw std::runtime_error("idk");
			}
		}

		this->expectToken(TokenType::CloseBracket);

		return std::make_shared<AST::ArrayLiteral>(arr);
	}