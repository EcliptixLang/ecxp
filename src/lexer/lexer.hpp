#pragma once
#include <vector>
#include <string>


enum class TokenType {
	Number,
	String,
	Identifier,
	BinaryOperator,
	Equals,
	BinaryEquals,
	ComparativeOperator,
	Comma,
	DollarSign,
	Dot,
	Colon,
	Semicolon,
	OpenParen,
	CloseParen,
	OpenBrace,
	CloseBrace,
	OpenBracket,
	CloseBracket,
	Slash,
	ExclamationMark,
	New,
	Set,
	Lock,
	Fun,
	If,
	Skip,
	Else,
	While,
	For,
	Return,
	Break,
	Async,
	From,
	Take,
	Give,
	At,
	Using,
	When,
	Type,
	Class,
	Uses,
	_EOF
};

struct Token {
    std::string value;
    TokenType type;
	int start;
	int end;
};

class Lexer {
	public:
		Lexer();
		~Lexer();
		std::vector<Token> tokenize(std::string sourceCode);
    	std::string StringifyTokenTypes(TokenType type);
	private:
		std::vector<Token> tokens;
};

#define TokenArr std::vector<Token>
#define KeywordList std::map<std::string, TokenType>
