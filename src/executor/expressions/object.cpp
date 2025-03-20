#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateObjectLiteral(const AST::ObjectLiteral& node, Runtime::Environment& env){
	std::map<string, std::unique_ptr<Values::Runtime>> props;

	for (const auto& val : node.properties) {
		AST::ObjectProperty* element = static_cast<AST::ObjectProperty*>(val.get());
		props[element->key] = std::move(this->evaluate(element->value, env));
	}

	return std::make_unique<Values::Object>(std::move(props));

}