#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateArrayLiteral(const AST::ArrayLiteral& node, std::shared_ptr<Runtime::Environment> &env){
	std::vector<std::shared_ptr<Values::Runtime>> array{};

	for(auto& val : node.elements){
		std::shared_ptr<Values::Runtime> v = this->evaluate(val, env);
		array.push_back(v);
	}

	return std::make_shared<Values::Array>(array);
}