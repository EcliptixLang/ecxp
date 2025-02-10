#pragma once
#include "../values.hpp"
#include "../ast.hpp"
#include "../utilities/env.hpp"
#include <memory>

class Compiler {
    public:
        void CProgram(std::shared_ptr<AST::ExprAST>& astNode);
        void CNumber(std::shared_ptr<AST::ExprAST>& astNode);
        void CCall(std::shared_ptr<AST::ExprAST>& astNode);
        void CVariable(std::shared_ptr<AST::ExprAST>& astNode);
        void CString(std::shared_ptr<AST::ExprAST>& astNode);
        void CIdent(std::shared_ptr<AST::ExprAST>& astNode);
        void CBinary(std::shared_ptr<AST::ExprAST>& astNode);
        void CObject(std::shared_ptr<AST::ExprAST>& astNode);
        void CArray(std::shared_ptr<AST::ExprAST>& astNode);
        void CMember(std::shared_ptr<AST::ExprAST>& astNode);
        void CFunction(std::shared_ptr<AST::ExprAST>& astNode);
        void CAssignment(std::shared_ptr<AST::ExprAST>& astNode);
        void CWhile(std::shared_ptr<AST::ExprAST>& astNode);
        void CIf(std::shared_ptr<AST::ExprAST>& astNode);
        void CEqu(std::shared_ptr<AST::ExprAST>& astNode);
        void compile(std::shared_ptr<AST::ExprAST>& astNode);
        void save(std::string filename);
    private:
        std::string code = "";
        std::unordered_map<std::string, bool> libs;
        int indent = 0;
};