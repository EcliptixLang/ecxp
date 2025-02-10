#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CProgram(std::shared_ptr<AST::ExprAST>& astNode) {
	AST::Program* program = dynamic_cast<AST::Program*>(astNode.get());
    if (!program) {
        throw std::runtime_error("Invalid AST Node: Expected AST::Program.");
    }
    
    int i = 0;
    std::shared_ptr<Values::Runtime> val;

    while (i < program->body.size()) {
        std::shared_ptr<AST::ExprAST> expr = program->body[i];
        this->compile(expr);
        code += "\n";
        i++;
        code += "\n";
    }
}