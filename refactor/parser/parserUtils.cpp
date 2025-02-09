#include "parser.hpp"
#include <iostream>

bool Parser::NotEOF() {
  return this->Tokens[0].type != TokenType::_EOF;
}

Token Parser::currentToken() {
  return this->Tokens[0];
}

Token Parser::previousToken() {
  return this->lastToken;
}

Token Parser::nextToken() {
  lastToken = this->currentToken();
  return Utilities::shift(this->Tokens);
}

Token Parser::expectToken(TokenType type){
    Token tok = Utilities::shift(this->Tokens);

	if(tok.type != type){
		std::cout << "Unexpected token found during parsing\n- Value: " << this->currentToken().value << "\n- Type: " << lexer.StringifyTokenTypes(this->currentToken().type) << "\n- Expected type: " << lexer.StringifyTokenTypes(type);
    	exit(1);
	}

	return tok;
}

Token Parser::expectOne(TokenType type1, TokenType type2){
  Token tok = this->Tokens[0];

	if(lexer.StringifyTokenTypes(tok.type) != lexer.StringifyTokenTypes(type1) && lexer.StringifyTokenTypes(tok.type) != lexer.StringifyTokenTypes(type2)){
		std::cout << "Unexpected token found during parsing\n- Value: " << this->currentToken().value << "\n- Type: " << lexer.StringifyTokenTypes(this->currentToken().type) << "\n- Expected types: " << lexer.StringifyTokenTypes(type1) << ", "<< lexer.StringifyTokenTypes(type2);
    	exit(1);
	}

	return tok;
}