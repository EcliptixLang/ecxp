#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateMemberAccess(
    const AST::MemberAccessExpr& node, 
    Environment& env
) {
    std::unique_ptr<Values::Runtime> val = this->evaluate(node.object, env);
    
    AST::IdentifierExpr* id = static_cast<AST::IdentifierExpr*>(node.property.get());
    if (!id) throw InterpreterError("Invalid member access property");
    string sym = id->name;

    if (val->type() == Values::Type::Object) {
        Values::Object* obj = static_cast<Values::Object*>(val.get());
        const auto& props = obj->properties();
        
        if (auto it = props.find(sym); it != props.end()) {
            return it->second->clone();
        }
        throw InterpreterError("Property '" + sym + "' doesn't exist on object");
    }
    else if (val->type() == Values::Type::String) {
        Values::String* str = static_cast<Values::String*>(val.get());
        
        if (sym == "length") {
            return std::make_unique<Values::Number>(str->value().size());
        }
        throw InterpreterError("Strings only have 'length' property");
    }
    
    throw InterpreterError("Cannot access property on non-object value");
}