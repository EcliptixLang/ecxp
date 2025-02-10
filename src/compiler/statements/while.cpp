#include "../compiler.hpp"

using Nodes = AST::Nodes; 
using string = std::string;

void Compiler::CWhile(std::shared_ptr<AST::ExprAST>& astNode){
    bool truu = true;
    AST::WhileDeclaration* whilee = dynamic_cast<AST::WhileDeclaration*>(astNode.get());
    
    code += "while(";

    this->compile(whilee->conditional);
    
    code += ") {";
    indent++;

    for(auto& thing : whilee->consequent){
        this->compile(thing);
    }

    indent--;

    code += "}";

}