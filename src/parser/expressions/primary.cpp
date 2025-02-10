#include "../parser.hpp"
#include <iostream>

PAST Parser::ParsePrimary() {
        Token token = this->currentToken();

        switch (token.type) {
            case TokenType::Identifier:
				return std::make_shared<AST::Identifier>(AST::Identifier(this->nextToken().value));
            case TokenType::Number:
                return std::make_shared<AST::NumberExpr>(AST::NumberExpr(std::stod(this->nextToken().value)));
			case TokenType::Break:
				this->nextToken();
                return std::make_shared<AST::Break>(AST::Break());
			case TokenType::String:
				return std::make_shared<AST::StringExpr>(AST::StringExpr(this->nextToken().value));
			case TokenType::Return:
				this->nextToken();
				return std::make_shared<AST::ReturnExpr>(this->ParseExpression());

			case TokenType::OpenParen:{
				this->nextToken();
				PAST left = this->ParseExpression();
				PAST right;
				PAST value;
				Token oper;
				if(this->currentToken().type == TokenType::ComparativeOperator){
					oper = this->nextToken();
					right = this->ParseExpression();
					value = std::make_shared<AST::EquExpr>(left, right, oper);
				}else {
					value = left;
				}
				this->expectToken(TokenType::CloseParen);
				return value;
			}
            default:
                std::cout << "\033[31mParser Error\033[0m: Unexpected token found during parsing\n- Value: \033[36m" << this->currentToken().value << "\033[0m\n- Type: \033[36m" << lexer.StringifyTokenTypes(this->currentToken().type) << "\033[0m\n- past: " << lexer.StringifyTokenTypes(this->lastToken.type) << "\n";
                exit(1);
        }
}