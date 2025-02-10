#include "../parser.hpp"

PAST Parser::parseMemberCalls() {
		PAST member = 
			this->parseMember();
		if(
			this->currentToken().type == 
			TokenType::OpenParen
		){
			return this->parseCalls(member);
		}

		return member;
	}