#include "./lexer.hpp"
#include "../utilities/utils.hpp"
#include <iostream>
#include <map>
#include "../config.hpp"
#include <string>
#include <vector>

Lexer::Lexer(){

}

Lexer::~Lexer(){

}

std::map<std::string, TokenType> Keywords()
{
    KeywordList keywords;
    keywords["Number"] = TokenType::Type;
    keywords["Float"] = TokenType::Type;
    keywords["Boolean"] = TokenType::Type;
    keywords["String"] = TokenType::Type;
    keywords["Array"] = TokenType::Type;
    keywords["Object"] = TokenType::Type;

    keywords["set"] = TokenType::Set;
    keywords["lock"] = TokenType::Lock;
    keywords["fun"] = TokenType::Fun;
    keywords["if"] = TokenType::If;
    keywords["else"] = TokenType::Else;
    keywords["for"] = TokenType::For;
    keywords["while"] = TokenType::While;
    keywords["return"] = TokenType::Return;
    keywords["break"] = TokenType::Break;
    keywords["take"] = TokenType::Take;
    keywords["from"] = TokenType::From;
    keywords["give"] = TokenType::Give;
    keywords["using"] = TokenType::Using;
    keywords["when"] = TokenType::When;
    keywords["skip"] = TokenType::Skip;
    keywords["class"] = TokenType::Class;
    keywords["uses"] = TokenType::Uses;
    return keywords;
}

Token token(std::string value, TokenType type, int start, int end)
{
    return {value, type, start, end};
}

bool skippable(char src)
{
    return src == ' ' || src == '\n' || src == '\t' || src == '\b';
}

std::string sstr(std::vector<char> &src){
    return std::to_string(Utilities::shift(src));
}


TokenArr Lexer::tokenize(std::string sourceCode)
{
    KeywordList keywords = Keywords();
    TokenArr tokens{};
    int place = 0;
    int pos = 0;
    std::string src = sourceCode;

    while (src.size() > pos)
    {
        switch (src[pos])
        {
        case ')':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::CloseParen, place++, place));
            break;

        case '(':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::OpenParen, place++, place));
            break;

        case '{':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::OpenBrace, place++, place));
            break;

        case '}':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::CloseBrace, place++, place));
            break;

        case '[':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::OpenBracket, place++, place));
            break;

        case ']':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::CloseBracket, place++, place));
            break;

        case '=':
            pos++;
            if (src[pos] != '=')
                tokens.push_back(token("=", TokenType::Equals, place++, place));
            else
            {
                pos++;
                tokens.push_back(token("==", TokenType::ComparativeOperator, place++, place++));
            }
            break;

        case '$':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::DollarSign, place++, place));
            break;

        case ';':
            tokens.push_back(token(std::to_string(src[pos++]), TokenType::Semicolon, place++, place));
            break;

        case '@':
            pos++;
            if (src[pos] == '=')
            {
                pos++;
                tokens.push_back(token("@=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("@", TokenType::At, place++, place));
            }
            break;
        case '!':
            pos++;
            if (src[pos] == '=')
            {
                pos++;
                tokens.push_back(token("!=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("!", TokenType::ExclamationMark, place++, place));
            }
            break;

        case '<':
            pos++;
            if (src[pos+1] == '=')
            {
                pos++;
                tokens.push_back(token("<=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("<", TokenType::ComparativeOperator, place++, place));
            }
            break;

        case '>':
            pos++;
            if (src[pos+1] == '=')
            {
                pos++;
                tokens.push_back(token(">=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token(">", TokenType::ComparativeOperator, place++, place));
            }
            break;

        case ':':
            pos++;
            tokens.push_back(token(":", TokenType::Colon, place, place + 1));
            place++;
            break;

        case ',':
            pos++;
            tokens.push_back(token(",", TokenType::Comma, place, place + 1));
            place++;
            break;

        case '.':
            pos++;
            tokens.push_back(token(".", TokenType::Dot, place, place + 1));
            place++;
            break;

        case '\'':
        case '\"':
        {
            char odk = src[pos++];
            int start = place++;
            std::string str = "";
            while (src.size() > 0 && src[pos] != odk)
            {
                str += src[pos++];
                place++;
            }
            pos++;
            tokens.push_back(token(str, TokenType::String, start, place++));
        }
        break;

        case '*':
        case '+':
        case '-':
        case '/':
            if (src[pos] == '/' && src[pos+1] == '/' || src[pos+1] == '*')
            {
                char commentType = src[pos+1];
                int start = place++;
                pos += 2;
                place++;

                if (commentType == '/')
                {
                    while (!src.empty() && src[pos] != '\n')
                    {
                        pos++;
                        place++;
                    }
                }

                if (commentType == '*')
                {
                    pos++;
                    while (!src.empty())
                    {
                        if (src[pos] == '*' && src.size() > 1 && src[pos] == '/')
                        {
                            pos += 2;
                            break;
                        }
                        place++;
                        pos++;
                    }
                }
            }
            else
            {
                std::string idk = "";
                idk += std::to_string(src[pos++]);
                tokens.push_back(token(idk, TokenType::BinaryOperator, place++, place));
            }
            break;

        default:
            if (isalpha(src[pos]))
            {
                std::string idk = "";
                int start = place++;
                while (src.size() > 0 && isalnum(src[pos]))
                {
                    char text = src[pos++];
                    idk += text;
                    place++;
                }
                if (keywords.find(idk) == keywords.end())
                {
                    tokens.push_back(token(idk, TokenType::Identifier, start, place++));
                }
                else
                {
                    tokens.push_back(token(idk, keywords[idk], start, place++));
                }
            }
            else if (isdigit(src[pos]))
            {
                std::string idk = "";
                int start = place++;
                while (src.size() > 0 && isdigit(src[pos]))
                {
                    idk += std::to_string(src[pos++]);
                    place++;
                }
                tokens.push_back(token(idk, TokenType::Number, start, place++));
            }
            else if (skippable(src[pos]))
            {
                pos++;
                place++;
            }
            else
            {
                std::cout << "Unrecognized character found: " << src[pos] << std::endl;
                exit(1);
            }
            break;
        }
    }

    tokens.push_back(token("EndOfFile", TokenType::_EOF, ++place, ++place));
    return tokens;
}