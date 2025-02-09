#include <Interpreter.hpp>
#include <FunctionValues.hpp>
#include <ClassValues.hpp>

using Nodes = AST::Nodes; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::IClass(std::shared_ptr<AST::ExprAST>& astNode, Environment& env){
	AST::Class* Cluss = dynamic_cast<AST::Class*>(astNode.get());
	Environment enva; enva.setup();

	for(auto& thing : Cluss->body){
		this->evaluate(thing, enva);
	}

	Class clss(std::move(&enva), Cluss->name, Cluss->parent);

	env.setVariable(Cluss->name, std::make_shared<Class>(clss), "class", true);
	return createNull();
}