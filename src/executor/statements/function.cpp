#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateFunctionDeclaration(const AST::FunctionDeclaration& node, Runtime::Environment& env){
	std::unique_ptr<Values::Function> func = std::make_unique<Values::Function>(node.body, node.parameters, node.name, node.returnType);
	env.set(node.name, std::move(func));

	return std::make_unique<Values::Null>();
}