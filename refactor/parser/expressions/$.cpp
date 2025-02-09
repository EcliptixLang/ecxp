#include "../parser.hpp"

PAST Parser::parseDSNotation() {
		if(this->Tokens[0].type != TokenType::DollarSign){
			return this->parseObjects();
		}
		this->nextToken();
		Token idk = this->expectToken(TokenType::String);

		return std::make_shared<AST::ShellCMD>(idk.value);
	}