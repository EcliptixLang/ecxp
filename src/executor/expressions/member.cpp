#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateMemberAccess(const AST::MemberAccessExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::shared_ptr<Values::Runtime> val = this->evaluate(node.object, env);
	AST::IdentifierExpr* id = dynamic_cast<AST::IdentifierExpr*>(node.property.get());
	string sym = id->name;

	if(val->type() == "Object"){
		Values::Object* obj = dynamic_cast<Values::Object*>(val.get());
		auto it = obj->properties().find(sym);
        if (it != obj->properties().end()) {
            return it->second;
        } else {
            throw InterpreterError("Property '" + sym + "' doesn't exist on object");
        }
	} else {
		if(val->type() == "String"){
			string value = dynamic_cast<Values::String*>(val.get())->value();
			return val;
		}
	}
	throw std::runtime_error("Cannot access property on non-object value");
}