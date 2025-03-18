#pragma once
#include "../lexer/lexer.hpp"
#include "../ast.hpp"
#include "../utilities/utils.hpp"
#include "../config.hpp"
#define PAST std::shared_ptr<AST::ExprAST>
class Parser {
    public:
        Parser() {}
        std::shared_ptr<AST::ProgramRoot> produceAST(std::string& sourceCode);
        Lexer lexer;
    private:
        int pos = 0;
        TokenArr Tokens{};
        Token lastToken;
        bool constanty = false;
        Settings settings;

		bool NotEOF();
		Token currentToken();
        Token previousToken();
        Token nextToken();
        Token expectOne(TokenType type1, TokenType type2);

        std::shared_ptr<AST::ExprAST> ParseStatement();
        std::shared_ptr<AST::ExprAST> parseWhen();
        std::shared_ptr<AST::ExprAST> parseWhile();
        std::shared_ptr<AST::ExprAST> parseIf();
        std::shared_ptr<AST::ExprAST> parseFunctions();
        std::shared_ptr<AST::ExprAST> parseVariables();
        std::shared_ptr<AST::ExprAST> parseNew();
        std::shared_ptr<AST::ExprAST> parseAssignment();
        std::shared_ptr<AST::ExprAST> parseArrays();
        std::shared_ptr<AST::ExprAST> parseDSNotation();
        std::shared_ptr<AST::ExprAST> parseObjects();
        std::shared_ptr<AST::ExprAST> parseMemberCalls();
        std::shared_ptr<AST::ExprAST> parseCalls(std::shared_ptr<AST::ExprAST> caller);
        std::vector<std::shared_ptr<AST::ExprAST>> parseArgs();
		std::vector<std::shared_ptr<AST::ExprAST>> parseArgsList();
        std::shared_ptr<AST::ExprAST> parseMember();
        std::shared_ptr<AST::ExprAST> ParseNewTypes();

        std::shared_ptr<AST::ExprAST> ParseExpression();
        std::shared_ptr<AST::ExprAST> ParseAdditiveExpression();
        std::shared_ptr<AST::ExprAST> ParsePrimary();
        std::shared_ptr<AST::ExprAST> ParseMultiplicativeExpression();
        Token expectToken(TokenType type);
};