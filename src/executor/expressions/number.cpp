#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateNumberLiteral(const AST::NumberLiteral& node){
	return std::make_unique<Values::Number>(Values::Number(node.value));
}