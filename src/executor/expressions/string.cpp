#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateStringLiteral(const AST::StringLiteral& node) {
    return std::make_shared<Values::String>(node.value);
}
