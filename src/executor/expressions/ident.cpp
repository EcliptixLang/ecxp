#include "../executor.hpp"
using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateIdentifier(const AST::IdentifierExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> val = env->get(node.name).value;
	return val;
}