#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateDSN(const AST::ShellCommandExpr &node, std::shared_ptr<Runtime::Environment> &env){
    system(node.command.c_str());
    return createNull();
}