#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CString(std::shared_ptr<AST::ExprAST>& astNode){
	AST::StringExpr* str = dynamic_cast<AST::StringExpr*>(astNode.get());
	code += "\"" + str->Value + "\"";
}