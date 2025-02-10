#include "lexer.hpp"

std::string Lexer::StringifyTokenTypes(TokenType type)
    {
        switch (type)
        {
        case TokenType::BinaryOperator:
            return "TokenType::BinaryOperator";
        case TokenType::CloseParen:
            return "TokenType::CloseParen";
        case TokenType::OpenParen:
            return "TokenType::OpenParen";
        case TokenType::Equals:
            return "TokenType::Equals";
        case TokenType::Identifier:
            return "TokenType::Identifier";
        case TokenType::Number:
            return "TokenType::Number";
        case TokenType::String:
            return "TokenType::String";
        case TokenType::Lock:
            return "TokenType::Lock";
        case TokenType::Set:
            return "TokenType::Set";
        case TokenType::Async:
            return "TokenType::Async";
        case TokenType::BinaryEquals:
            return "TokenType::BinaryEquals";
        case TokenType::Break:
            return "TokenType::Break";
        case TokenType::CloseBrace:
            return "TokenType::CloseBrace";
        case TokenType::CloseBracket:
            return "TokenType::CloseBracket";
        case TokenType::Colon:
            return "TokenType::Colon";
        case TokenType::Comma:
            return "TokenType::Comma";
        case TokenType::DollarSign:
            return "TokenType::DollarSign";
        case TokenType::Dot:
            return "TokenType::Dot";
        case TokenType::ComparativeOperator:
            return "TokenType::ComparativeOperator";
        case TokenType::Else:
            return "TokenType::Else";
        case TokenType::For:
            return "TokenType::For";
        case TokenType::From:
            return "TokenType::From";
        case TokenType::Fun:
            return "TokenType::Fun";
        case TokenType::Give:
            return "TokenType::Give";
        case TokenType::If:
            return "TokenType::If";
        case TokenType::OpenBrace:
            return "TokenType::OpenBrace";
        case TokenType::OpenBracket:
            return "TokenType::OpenBracket";
        case TokenType::Return:
            return "TokenType::Return";
        case TokenType::Semicolon:
            return "TokenType::Semicolon";
        case TokenType::Slash:
            return "TokenType::Slash";
        case TokenType::Take:
            return "TokenType::Take";
        case TokenType::Using:
            return "TokenType::Using";
        case TokenType::When:
            return "TokenType::When";
        case TokenType::While:
            return "TokenType::While";
        case TokenType::Class:
            return "TokenType::Class";
        case TokenType::Uses:
            return "TokenType::Uses";
        case TokenType::_EOF:
            return "TokenType::_EOF";

        default:
            return "unknown";
        }
    }