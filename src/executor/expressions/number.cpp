#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateNumberLiteral(const AST::NumberLiteral& node){
	return std::make_shared<Values::Number>(Values::Number(node.value));
}