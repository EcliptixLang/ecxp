#include "../parser.hpp"

PAST Parser::parseFunctions() {
		Token token = this->nextToken();

		std::string name = 
			this->expectToken(TokenType::Identifier).value;

		std::vector<PAST> args = 
			this->parseArgs();

		std::vector<std::string> params{};

		for(auto& arg : args){
			AST::ExprAST* expr = arg.get();
			if(expr->getType() != AST::Nodes::Identifier){
				throw "Parameters expected inside function declaration";
			}

	      	AST::Identifier* id = dynamic_cast<AST::Identifier*>(
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


		return std::make_shared<AST::Function>(params, name, body, "auto");
}