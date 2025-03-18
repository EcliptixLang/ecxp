#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateObjectLiteral(const AST::ObjectLiteral& node, std::shared_ptr<Runtime::Environment> &env){
	std::map<string, std::shared_ptr<Values::Runtime>> props;

	for (const auto& val : node.properties) {
		AST::ObjectProperty* element = dynamic_cast<AST::ObjectProperty*>(val.get());
		props[element->key] = (this->evaluate(element->value, env));
	}

	return std::make_shared<Values::Object>(props);

}