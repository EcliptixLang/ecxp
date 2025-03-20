#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateDSN(const AST::ShellCommandExpr &node, Environment& env){
    system(node.command.c_str());
    return createNull();
}