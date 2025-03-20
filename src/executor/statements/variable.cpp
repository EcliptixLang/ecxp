#include "../executor.hpp"
#include <memory>

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateVariableDeclaration(const AST::VariableDeclarationExpr& node, Environment& env){
	std::unique_ptr<Values::Runtime> val = this->evaluate(node.initialValue, env);

	if(val->stringType() == node.typeHint || node.typeHint == "auto"){
		env.set(node.identifier, std::move(val));
		return std::make_unique<Values::Null>();
	} else if(val->type() == Values::Type::ReturnedValue){
		Values::ReturnedValue* ret = static_cast<Values::ReturnedValue*>(val.get());
		env.set(node.identifier, ret->takeValue());
		return std::make_unique<Values::Null>();
	} else {
		std::cout << "Error while declaring variable '" << node.identifier << "', because it seems like it's requiring type '" << node.typeHint << "' and the value applied to it was of type '" << val->stringType() << "'.\n";
		exit(6);
	}
}