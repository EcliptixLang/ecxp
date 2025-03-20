#include "../parser.hpp"

PAST Parser::parseCalls(PAST caller) {
	AST::NumberLiteral* expr = static_cast<AST::NumberLiteral*>(
		caller.get()
	);

    if(expr){
      if(expr->nodeType() == AST::NodeType::NumberLiteral)
  			this->ParsePrimary();
	}

	std::vector<PAST> args = this->parseArgs();
	PAST call = std::make_shared<AST::FunctionCallExpr>(caller, args);
		
	if(this->currentToken().type == TokenType::OpenParen){
		call = this->parseCalls(call);
	}

	return call;
}