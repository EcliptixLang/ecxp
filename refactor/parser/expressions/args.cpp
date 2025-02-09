#include "../parser.hpp"

std::vector<PAST> Parser::parseArgs() {
	this->expectToken(TokenType::OpenParen);
	std::vector<PAST> args{};
	if(this->currentToken().type != TokenType::CloseParen) args = this->parseArgsList();
	this->expectToken(TokenType::CloseParen);
	return args;
}

std::vector<PAST> Parser::parseArgsList() {
	std::vector<PAST> args{};
	args.push_back(this->parseAssignment());
	while(this->currentToken().type == TokenType::Comma){
		this->nextToken();
		args.push_back(this->parseAssignment());
	}

	return args;
}