#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateArrayLiteral(const AST::ArrayLiteral& node, Runtime::Environment& env){
	std::vector<std::unique_ptr<Values::Runtime>> array{};

	for(auto& val : node.elements){
		std::unique_ptr<Values::Runtime> v = this->evaluate(val, env);
		array.push_back(std::move(v));
	}

	return std::make_unique<Values::Array>(std::move(array));
}