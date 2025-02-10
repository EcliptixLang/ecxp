#include "parser.hpp"
#include <iostream>

bool Parser::NotEOF() {
  return this->Tokens[pos].type != TokenType::_EOF;
}

Token Parser::currentToken() {
  return this->Tokens[pos];
}

Token Parser::previousToken() {
  return this->lastToken;
}

Token Parser::nextToken() {
  lastToken = this->currentToken();
  pos++;
  return lastToken;
}

Token Parser::expectToken(TokenType type){
	Token tok = this->Tokens[pos];
    pos++;

	if(tok.type != type){
		std::cout << "Unexpected token found during parsing\n- Value: " << this->currentToken().value << "\n- Type: " << lexer.StringifyTokenTypes(this->currentToken().type) << "\n- Expected type: " << lexer.StringifyTokenTypes(type);
    	exit(1);
	}

	return tok;
}

Token Parser::expectOne(TokenType type1, TokenType type2){
  Token tok = this->Tokens[pos];

	if(tok.type != type1 && tok.type != type2){
		std::cout << "Unexpected token found during parsing\n- Value: " << this->currentToken().value << "\n- Type: " << lexer.StringifyTokenTypes(this->currentToken().type) << "\n- Expected types: " << lexer.StringifyTokenTypes(type1) << ", "<< lexer.StringifyTokenTypes(type2);
    	exit(1);
	}

	return tok;
}