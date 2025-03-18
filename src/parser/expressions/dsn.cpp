#include "../parser.hpp"

PAST Parser::parseDSNotation() {
		if(this->Tokens[pos].type != TokenType::DollarSign){
			return this->parseObjects();
		}
		this->nextToken();
		Token idk = this->expectToken(TokenType::String);

		return std::make_shared<AST::ShellCommandExpr>(idk.value);
	}