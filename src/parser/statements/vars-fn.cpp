#include "../parser.hpp"
#include <algorithm>
#include <iostream>

PAST Parser::ParseNewTypes(){
	bool isArray = false;
	int size = 0;
	std::string type = this->expectToken(TokenType::Type).value;

	if(this->currentToken().type == TokenType::OpenBracket){
		this->nextToken();
		isArray = true;
		Token tok = this->expectToken(TokenType::Number);
		size = std::stoi(tok.value);
		this->expectToken(TokenType::CloseBracket);
	}
	if(this->currentToken().type == TokenType::Dot){
		pos--;
		return this->ParseExpression();
	}

	std::string name = this->expectToken(TokenType::Identifier).value;

	TokenType thing = this->expectOne(TokenType::OpenParen, TokenType::Equals).type;

	if(thing == TokenType::OpenParen){
		std::vector<PAST> args = 
			this->parseArgs();

		std::vector<std::string> params{};

		for(auto& arg : args){
			AST::ExprAST* expr = arg.get();
			if(expr->nodeType() != AST::NodeType::IdentifierExpr){
				throw "Parameters expected inside function declaration";
			}

	      	AST::IdentifierExpr* id = static_cast<AST::IdentifierExpr*>(
				arg.get()
			);
			
			params.push_back(id->name);
		}

		this->expectToken(TokenType::OpenBrace);

		std::vector<PAST> body{};

		while(
			this->NotEOF() &&
			this->currentToken().type 
				!= TokenType::CloseBrace
		){
			body.push_back(this->ParseStatement());
		}

		this->expectToken(TokenType::CloseBrace);

		return std::make_shared<AST::FunctionDeclaration>(params, name, body, type);
	} else if(thing == TokenType::Equals){
		this->nextToken();
		PAST value = this->ParseStatement();
		bool cty = false;
		if(constanty)
			cty = true;
		constanty = false;
		return std::make_shared<AST::VariableDeclarationExpr>(name, type, value, cty);
	} else {
		std::cout << "unknown error " << lexer.StringifyTokenTypes(thing) << std::endl;
		exit(9);
	}
}