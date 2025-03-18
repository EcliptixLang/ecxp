#include "../executor.hpp"
#include <memory>

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateVariableDeclaration(const AST::VariableDeclarationExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> val = this->evaluate(node.initialValue, env);

	if(val->type() == node.typeHint || node.typeHint == "auto"){
		env->set(node.identifier, val, node.isConstant);
		return val;
	} else if(val->type() == "return"){
		Values::ReturnedValue* ret = dynamic_cast<Values::ReturnedValue*>(val.get());
		env->set(node.identifier, ret->value(), node.isConstant);
		return ret->value();
	} else {
		std::cout << "Error while declaring variable '" << node.identifier << "', because it seems like it's requiring type '" << node.typeHint << "' and the value applied to it was of type '" << val->type() << "'.\n";
		exit(6);
	}
}