#include "../executor.hpp"
using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateIdentifier(const AST::IdentifierExpr& node, Environment& env){
	auto* hi = env.get(node.name);
	return hi->clone();
}