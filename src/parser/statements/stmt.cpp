#include "../parser.hpp"

PAST Parser::ParseStatement() {
  switch(this->currentToken().type){
		case TokenType::Set: case TokenType::Lock:{
			Token token = this->nextToken();
			if(token.value == "lock")
				constanty = true;
			return this->ParseNewTypes();
		}
		case TokenType::Fun:
			return this->parseFunctions();
		case TokenType::If:
			return this->parseIf();
		case TokenType::When:
			return this->parseWhen();
		case TokenType::While:
			return this->parseWhile();
		case TokenType::DollarSign:
			return this->parseDSNotation();
		default:
			return this->ParseExpression();
	}
}