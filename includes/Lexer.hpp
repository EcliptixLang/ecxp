#pragma once
#include <vector>
#include <string>
#include <map>
#include "Utilities.hpp"
#include <config.hpp>

#define TokenArr std::vector<Lexer::Token>
#define KeywordList std::map<std::string, Lexer::TokenType>

namespace Lexer {
    enum class TokenType {
		Number,
		Identifier,
		String,
		BinaryOperator,
		Equals,
		BinaryEquals,
		ComparativeOperator,
		Comma,
		DollarSign,
		Dot,
		Colon,
		New,
		Semicolon,
		OpenParen, 
		CloseParen, 
		OpenBrace, 
		CloseBrace,
	    OpenBracket, 
		CloseBracket,
		Slash,
		Set,
		ExclamationMark,
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
		NL,
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

    TokenArr tokenize(std::string sourceCode, Settings settings);
    std::string StringifyTokenTypes(TokenType type);
}
