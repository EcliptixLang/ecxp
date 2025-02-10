#include "../parser.hpp"

PAST Parser::parseCalls(PAST caller) {
	AST::NumberExpr* expr = dynamic_cast<AST::NumberExpr*>(
		caller.get()
	);

    if(expr){
      if(expr->getType() == AST::Nodes::Number)
  			this->ParsePrimary();
	}

	std::vector<PAST> args = this->parseArgs();
	PAST call = std::make_shared<AST::CallExpr>(caller, args);
		
	if(this->currentToken().type == TokenType::OpenParen){
		call = this->parseCalls(call);
	}

	return call;
}