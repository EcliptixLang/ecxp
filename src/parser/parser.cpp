#include "parser.hpp"

std::shared_ptr<AST::ProgramRoot> Parser::produceAST(
	std::string& sourceCode
){
	Tokens = lexer.tokenize(sourceCode);
	std::vector<PAST> body{};
  
	while(this->NotEOF()){
		body.push_back(this->ParseStatement());
	}
	
	return std::make_shared<AST::ProgramRoot>(body);
}