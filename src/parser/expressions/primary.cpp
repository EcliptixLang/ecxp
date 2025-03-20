#include "../parser.hpp"
#include <iostream>

PAST Parser::ParsePrimary() {
        Token token = this->currentToken();

        switch (token.type) {
            case TokenType::Identifier:
				return std::make_shared<AST::IdentifierExpr>(this->nextToken().value);
			case TokenType::Number: {
			    Token numToken = this->nextToken();
			    return std::make_shared<AST::NumberLiteral>(std::stod(numToken.value));
			}
			case TokenType::Break:
				this->nextToken();
                return std::make_shared<AST::BreakStatement>();
			case TokenType::String:
				return std::make_shared<AST::StringLiteral>(this->nextToken().value);
			case TokenType::Return:
				this->nextToken();
				return std::make_shared<AST::ReturnStatement>(this->ParseExpression());

			case TokenType::OpenParen:{
				this->nextToken();
				PAST left = this->ParseExpression();
				PAST right;
				PAST value;
				Token oper;
				if(this->currentToken().type == TokenType::ComparativeOperator){
					oper = this->nextToken();
					right = this->ParseExpression();
					value = std::make_shared<AST::EqualityCheckExpr>(left, right, oper);
				}else {
					value = left;
				}
				this->expectToken(TokenType::CloseParen);
				return value;
			}
            default:
                std::cout << "\033[31mParser Error\033[0m: Unexpected token found during parsing\n- Value: \033[36m" << this->currentToken().value << "\033[0m\n- Type: \033[36m" << lexer.StringifyTokenTypes(this->currentToken().type) << "\033[0m\n- past: " << lexer.StringifyTokenTypes(this->lastToken.type) << std::endl;
                exit(1);
        }
}