#include <Lexer.hpp>
#include <iostream>
#include <config.hpp>

std::string trst(std::string str, Settings settings){
    if(settings.types.automatic == str){
        return "Auto";
    }

    if(settings.types.array == str){
        return "Array";
    }

    if(settings.types.boolean == str){
        return "Boolean";
    }

    if(settings.types.null == str){
        return "Null";
    }

    if(settings.types.number == str){
        return "Number";
    }

    if(settings.types.object == str){
        return "Object";
    }

    if(settings.types.shell == str){
        return "Shell";
    }

    if(settings.types.string == str){
        return "String";
    }

    return str;
}

namespace Lexer {

    KeywordList Keywords(Settings settings) {
        KeywordList keywords;
        keywords["new"] = TokenType::New;
        keywords[settings.types.automatic] = TokenType::Type;
        keywords[settings.types.boolean] = TokenType::Type;
        keywords[settings.types.array] = TokenType::Type;
        keywords[settings.types.number] = TokenType::Type;
        keywords[settings.types.object] = TokenType::Type;
        keywords[settings.types.string] = TokenType::Type;
        keywords[settings.types.null] = TokenType::Type;
        keywords[settings.types.shell] = TokenType::Type;
        keywords[settings.keywords.set] = TokenType::Set;
        keywords[settings.keywords.lock] = TokenType::Lock;
		keywords[settings.keywords.fun] = TokenType::Fun;
		keywords[settings.keywords._if] = TokenType::If;
		keywords[settings.keywords._else] = TokenType::Else;
		keywords[settings.keywords._for] = TokenType::For;
		keywords[settings.keywords._while] = TokenType::While;
		keywords[settings.keywords._return] = TokenType::Return;
		keywords[settings.keywords._break] = TokenType::Break;
		keywords[settings.keywords.take] = TokenType::Take;
		keywords[settings.keywords.from] = TokenType::From;
		keywords[settings.keywords.give] = TokenType::Give;
		keywords[settings.keywords._using] = TokenType::Using;
		keywords[settings.keywords.when] = TokenType::When;
        keywords[settings.keywords.skip] = TokenType::Skip;
        keywords[settings.keywords._class] = TokenType::Class;
        keywords[settings.keywords.uses] = TokenType::Uses;
        return keywords;
    }

    Token token(std::string value, TokenType type, int start, int end) {
        return { value, type, start, end };
    }

    bool skippable(char src) {
        return src == ' ' || src == '\n' || src == '\t' || src == '\b';
    }

    TokenArr tokenize(std::string sourceCode, Settings settings) {
        KeywordList keywords = Keywords(settings);
        TokenArr tokens{};
        int place = 0;
        CharArr src = Utilities::split(sourceCode);

        while (src.size() > 0) {
            switch (src[0]) {
                case ')':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::CloseParen, place++, place));
                break;

                case '(':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::OpenParen, place++, place));
                break;

                case '{':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::OpenBrace, place++, place));
                break;

                case '}':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::CloseBrace, place++, place));
                break;

                case '[':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::OpenBracket, place++, place));
                break;

                case ']':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::CloseBracket, place++, place));
                break;

                case '=':
                    Utilities::shift(src);
    				if(src[0] != '=')
                        tokens.push_back(token("=", TokenType::Equals, place++, place));
                    else {
                        Utilities::shift(src);
			    		tokens.push_back(token("==", TokenType::ComparativeOperator, place++, place++));
                    }             	
                break;

                case '$':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::DollarSign, place++, place));
                break;

                case ';':
                    tokens.push_back(token(std::to_string(Utilities::shift(src)), TokenType::Semicolon, place++, place));
                break;

                case '@':
                    Utilities::shift(src);
                    if(src[0] == '='){
                        Utilities::shift(src);
                        tokens.push_back(token("@=", TokenType::ComparativeOperator, place++, place++));
                    } else {
                        tokens.push_back(token("@", TokenType::At, place++, place));
                    }
                break;
                case '!':
                    Utilities::shift(src);
                    if(src[0] == '='){
                        Utilities::shift(src);
                        tokens.push_back(token("!=", TokenType::ComparativeOperator, place++, place++));
                    } else {
                        tokens.push_back(token("!", TokenType::ExclamationMark, place++, place));
                    }
                break;
                
                case '<':
                    Utilities::shift(src);
                    if(src[1] == '='){
                        Utilities::shift(src);
                        tokens.push_back(token("<=", TokenType::ComparativeOperator, place++, place++));
                    } else {
                        tokens.push_back(token("<", TokenType::ComparativeOperator, place++, place));
                    }
                break;
                
                case '>':
                    Utilities::shift(src);
                    if(src[1] == '='){
                        Utilities::shift(src);
                        tokens.push_back(token(">=", TokenType::ComparativeOperator, place++, place++));
                    } else {
                        tokens.push_back(token(">", TokenType::ComparativeOperator, place++, place));
                    }
                break;

                case ':':
                    Utilities::shift(src);
                    tokens.push_back(token(":", TokenType::Colon, place++, place));
                break;

                case ',':
                    Utilities::shift(src);
                    tokens.push_back(token(",", TokenType::Comma, place++, place));
                break;
                
                case '.':
                    Utilities::shift(src);
                    tokens.push_back(token(".", TokenType::Dot, place++, place));
                break;
                
                case '\'':
                case '\"': {
                    char odk = Utilities::shift(src);
                    int start = place++;
    				std::string str = "";
				    while(src.size() > 0 && src[0] != odk){
			    		str += Utilities::shift(src);
                        place++;
		    		}
                    Utilities::shift(src);
                    tokens.push_back(token(str, TokenType::String, start, place++));
                } break;

                case '*':
                case '+':
                case '-':
                case '/':
                    if (src[0] == '/' && src[1] == '/' || src[1] == '*') {
                        char commentType = src[1];
                        int start = place++;
                        Utilities::shift(src);
                        Utilities::shift(src);
                        place++;

                        if (commentType == '/'){
                            while (!src.empty() && src[0] != '\n') {
                                Utilities::shift(src);
                                place++;
                            }
                        }

                        if (commentType == '*'){
                            Utilities::shift(src);
                            while (!src.empty()) {
                                if (src[0] == '*' && src.size() > 1 && src[1] == '/') {
                                    Utilities::shift(src);
                                    Utilities::shift(src);
                                    break;
                                }
                                place++;
                                Utilities::shift(src);
                            }
                        }
                    } else {
                        std::string idk = "";
                        idk += Utilities::shift(src);
                        tokens.push_back(token(idk, TokenType::BinaryOperator, place++, place));
                    }
                break;
            
                default:
                    if (isalpha(src[0])) {
                        std::string idk = "";
                        int start = place++;
                        while (src.size() > 0 && isalnum(src[0])) {
                            char text = Utilities::shift(src);
    						idk += text;
                            place++;
                        }
                        if (keywords.find(idk) == keywords.end()) {
                            tokens.push_back(token(idk, TokenType::Identifier, start, place++));
                        } else {
                            tokens.push_back(token(trst(idk, settings), keywords[idk], start, place++));
                        }
                    } else if (isdigit(src[0])) {
                        std::string idk = "";
                        int start = place++;
                        while (src.size() > 0 && isdigit(src[0])) {
                            idk += Utilities::shift(src);
                            place++;
                        }
                        tokens.push_back(token(idk, TokenType::Number, start, place++));
                    } else if (skippable(src[0])) {
                        Utilities::shift(src);
                        place++;
                    } else {
                        std::cout << "Unrecognized character found: " << src[0] << std::endl;
                        exit(1);
                    }
                break;
            }
        }

        tokens.push_back(token("EndOfFile", TokenType::_EOF, ++place, ++place));
        std::cout << "Tokenized" << std::endl;
        return tokens;
    }

    std::string StringifyTokenTypes(TokenType type) {
        switch (type) {
            case TokenType::BinaryOperator:  return "TokenType::BinaryOperator";
            case TokenType::CloseParen:      return "TokenType::CloseParen";
            case TokenType::OpenParen:       return "TokenType::OpenParen";
            case TokenType::Equals:          return "TokenType::Equals";
            case TokenType::Identifier:      return "TokenType::Identifier";
            case TokenType::Number:          return "TokenType::Number";
            case TokenType::String:          return "TokenType::String";
            case TokenType::Lock:            return "TokenType::Lock";
            case TokenType::Set:             return "TokenType::Set";
			case TokenType::Async:           return "TokenType::Async";
			case TokenType::BinaryEquals:    return "TokenType::BinaryEquals";
			case TokenType::Break:           return "TokenType::Break";
			case TokenType::CloseBrace:      return "TokenType::CloseBrace";
			case TokenType::CloseBracket:    return "TokenType::CloseBracket";
			case TokenType::Colon:           return "TokenType::Colon";
			case TokenType::Comma:           return "TokenType::Comma";
			case TokenType::DollarSign:      return "TokenType::DollarSign";
			case TokenType::Dot:             return "TokenType::Dot";
			case TokenType::ComparativeOperator:    return "TokenType::ComparativeOperator";
			case TokenType::Else:            return "TokenType::Else";
			case TokenType::For:             return "TokenType::For";
			case TokenType::From:            return "TokenType::From";
			case TokenType::Fun:             return "TokenType::Fun";
			case TokenType::Give:            return "TokenType::Give";
			case TokenType::If:              return "TokenType::If";
			case TokenType::OpenBrace:       return "TokenType::OpenBrace";
			case TokenType::OpenBracket:     return "TokenType::OpenBracket";
			case TokenType::Return:          return "TokenType::Return";
			case TokenType::Semicolon:       return "TokenType::Semicolon";
			case TokenType::Slash:           return "TokenType::Slash";
			case TokenType::Take:            return "TokenType::Take";
			case TokenType::Using:           return "TokenType::Using";
			case TokenType::When:            return "TokenType::When";
			case TokenType::While:           return "TokenType::While";
            case TokenType::Class:           return "TokenType::Class";
            case TokenType::Uses:            return "TokenType::Uses";
			case TokenType::_EOF:            return "TokenType::_EOF";

            default:                         return "unknown";
        }
    }
}