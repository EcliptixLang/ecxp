#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateFunctionDeclaration(const AST::FunctionDeclaration& node, std::shared_ptr<Runtime::Environment> &env){	
	Values::Function fun(node.body, node.parameters, node.name, node.returnType);
	std::shared_ptr<Values::Function> func = std::make_shared<Values::Function>(fun);
	env->set(node.name, func, true);

	return func;
}