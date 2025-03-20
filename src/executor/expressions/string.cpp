#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateStringLiteral(const AST::StringLiteral& node) {
    return std::make_unique<Values::String>(node.value);
}
