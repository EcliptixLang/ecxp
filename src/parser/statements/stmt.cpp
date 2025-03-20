#include "../parser.hpp"

PAST Parser::ParseStatement()
{
	switch (this->currentToken().type)
	{
	case TokenType::Set:
	case TokenType::Lock:
	{
		Token token = this->nextToken();
		if (token.value == "lock")
			constanty = true;
		return this->ParseNewTypes();
	} break;

	case TokenType::Type: {
		return this->ParseNewTypes();
	} break;
	
	case TokenType::Fun:
		return this->parseFunctions();
	case TokenType::If:
		return this->parseIf();
	case TokenType::When:
		return this->parseWhen();
	case TokenType::While:
		return this->parseWhile();
	case TokenType::DollarSign:
		return this->parseDSNotation();
	case TokenType::Take:
	{
		this->nextToken();

		auto args = this->parseArgs();

		this->expectToken(TokenType::From);

		std::string val = this->expectToken(TokenType::String).value;

		std::vector<std::string> items;

		for (auto &thingy : args)
		{
			if (thingy->nodeType() == AST::NodeType::IdentifierExpr)
			{
				AST::IdentifierExpr *id = static_cast<AST::IdentifierExpr*>(thingy.get());
				items.push_back(id->name);
			}
		}

		return std::make_shared<AST::ImportStatement>(val, items);
	}
	default:
		return this->ParseExpression();
	}

	return this->ParseExpression();
}