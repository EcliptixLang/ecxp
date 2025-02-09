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
    std::vector<char> src = Utilities::split(sourceCode);

    while (src.size() > 0)
    {
        switch (src[0])
        {
        case ')':
            tokens.push_back(token(sstr(src), TokenType::CloseParen, place++, place));
            break;

        case '(':
            tokens.push_back(token(sstr(src), TokenType::OpenParen, place++, place));
            break;

        case '{':
            tokens.push_back(token(sstr(src), TokenType::OpenBrace, place++, place));
            break;

        case '}':
            tokens.push_back(token(sstr(src), TokenType::CloseBrace, place++, place));
            break;

        case '[':
            tokens.push_back(token(sstr(src), TokenType::OpenBracket, place++, place));
            break;

        case ']':
            tokens.push_back(token(sstr(src), TokenType::CloseBracket, place++, place));
            break;

        case '=':
            Utilities::shift(src);
            if (src[0] != '=')
                tokens.push_back(token("=", TokenType::Equals, place++, place));
            else
            {
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
            if (src[0] == '=')
            {
                Utilities::shift(src);
                tokens.push_back(token("@=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("@", TokenType::At, place++, place));
            }
            break;
        case '!':
            Utilities::shift(src);
            if (src[0] == '=')
            {
                Utilities::shift(src);
                tokens.push_back(token("!=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("!", TokenType::ExclamationMark, place++, place));
            }
            break;

        case '<':
            Utilities::shift(src);
            if (src[1] == '=')
            {
                Utilities::shift(src);
                tokens.push_back(token("<=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token("<", TokenType::ComparativeOperator, place++, place));
            }
            break;

        case '>':
            Utilities::shift(src);
            if (src[1] == '=')
            {
                Utilities::shift(src);
                tokens.push_back(token(">=", TokenType::ComparativeOperator, place++, place++));
            }
            else
            {
                tokens.push_back(token(">", TokenType::ComparativeOperator, place++, place));
            }
            break;

        case ':':
            Utilities::shift(src);
            tokens.push_back(token(":", TokenType::Colon, place, place + 1));
            place++;
            break;

        case ',':
            Utilities::shift(src);
            tokens.push_back(token(",", TokenType::Comma, place, place + 1));
            place++;
            break;

        case '.':
            Utilities::shift(src);
            tokens.push_back(token(".", TokenType::Dot, place, place + 1));
            place++;
            break;

        case '\'':
        case '\"':
        {
            char odk = Utilities::shift(src);
            int start = place++;
            std::string str = "";
            while (src.size() > 0 && src[0] != odk)
            {
                str += Utilities::shift(src);
                place++;
            }
            Utilities::shift(src);
            tokens.push_back(token(str, TokenType::String, start, place++));
        }
        break;

        case '*':
        case '+':
        case '-':
        case '/':
            if (src[0] == '/' && src[1] == '/' || src[1] == '*')
            {
                char commentType = src[1];
                int start = place++;
                Utilities::shift(src);
                Utilities::shift(src);
                place++;

                if (commentType == '/')
                {
                    while (!src.empty() && src[0] != '\n')
                    {
                        Utilities::shift(src);
                        place++;
                    }
                }

                if (commentType == '*')
                {
                    Utilities::shift(src);
                    while (!src.empty())
                    {
                        if (src[0] == '*' && src.size() > 1 && src[1] == '/')
                        {
                            Utilities::shift(src);
                            Utilities::shift(src);
                            break;
                        }
                        place++;
                        Utilities::shift(src);
                    }
                }
            }
            else
            {
                std::string idk = "";
                idk += Utilities::shift(src);
                tokens.push_back(token(idk, TokenType::BinaryOperator, place++, place));
            }
            break;

        default:
            if (isalpha(src[0]))
            {
                std::string idk = "";
                int start = place++;
                while (src.size() > 0 && isalnum(src[0]))
                {
                    char text = Utilities::shift(src);
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
            else if (isdigit(src[0]))
            {
                std::string idk = "";
                int start = place++;
                while (src.size() > 0 && isdigit(src[0]))
                {
                    idk += Utilities::shift(src);
                    place++;
                }
                tokens.push_back(token(idk, TokenType::Number, start, place++));
            }
            else if (skippable(src[0]))
            {
                Utilities::shift(src);
                place++;
            }
            else
            {
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