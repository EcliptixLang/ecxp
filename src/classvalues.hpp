#pragma once

#include "values.hpp"
#include "./utilities/env.hpp"
#include "./executor/executor.hpp"

class Class : public Values::Runtime {
	public:
		Environment* eenv;
		std::string name;
		std::string parent;
		Interpreter* intr = new Interpreter({});
	Class(Environment* eenv, std::string name, std::string parent = "class") {
            // Set parent environment if inheriting
            if (parent != "class") {
                auto parentVar = eenv->getParent()->getVariable(parent);
                if (parentVar.value) {
                    auto parentClass = std::dynamic_pointer_cast<Class>(parentVar.value);
                    if (parentClass) {
                        // Set parent environment
                        eenv->setParent(parentClass->eenv);
                    }
                }
            }
            this->eenv = eenv;
            this->name = name;
            this->parent = parent;
        }

	std::string type() const override {
		return "class";
	}

	std::string stringValue() const override {
		Values::Function* fun = dynamic_cast<Values::Function*>(eenv->getVariable("toString").value.get()); 
		for(auto& b : fun->body){
			std::shared_ptr<Values::Runtime> val = intr->evaluate(b, *eenv);
            if(val->type() == "return"){
                Values::ReturnedValue* valo = dynamic_cast<Values::ReturnedValue*>(val.get());
                if(valo->value.get()->type() == "string"){
                    return dynamic_cast<Values::String*>(valo->value.get())->value;
                }
            }
		}
		return "<Class "+ name +">";
	}

    std::shared_ptr<Values::Runtime> clone() const override {
        return std::make_shared<Class>(eenv, name, parent);
    }

    std::shared_ptr<Values::Object> objectify(){
        std::map<std::string, std::shared_ptr<Values::Runtime>> props;
        for(auto& Value : eenv->getVariables()){
            props[Value.name] = Value.value;
        }

        return std::make_shared<Values::Object>(props);
    }

		std::shared_ptr<Environment> construct(std::vector<std::shared_ptr<Values::Runtime>>& args) {
            // Create instance environment with class methods/properties
            Environment instanceEnv;
            instanceEnv.setParent(eenv);
            
            // Copy methods from parent chain
            Environment* current = eenv;
            while (current) {
                for (auto& var : current->getVariables()) {
                    // Only copy functions and non-constructor properties
                    if (var.type == "function" || 
                        (var.name != "constructor" && var.type != "class")) {
                        instanceEnv.setVariable(var.name, var.value->clone(), var.type, true);
                    }
                }
                current = current->getParent();
            }

            // Call constructor if it exists
            auto ctor = eenv->getVariable("constructor").value;
            if (ctor && ctor->type() == "function") {
                auto fn = std::dynamic_pointer_cast<Values::Function>(ctor);
                if (fn) {
                    // Create constructor environment
                    Environment fnEnv;
                    fnEnv.setParent(&instanceEnv);
                    
                    // Bind constructor arguments
                    for (size_t i = 0; i < fn->parameters.size() && i < args.size(); i++) {
                        fnEnv.setVariable(fn->parameters[i], args[i], args[i]->type(), false);
                    }

                    // Execute constructor
                    for (auto& expr : fn->body) {
                        intr->evaluate(expr, fnEnv);
                    }
                }
            }

            // Return instance object
            return std::make_shared<Environment>(instanceEnv);
        }

	std::shared_ptr<Values::Runtime> getMethod(const std::string& name) {
    // Check own methods first
    auto method = eenv->getVariable(name).value;
    if(method) return method;

    // Check parent class
    if(parent != "class") {
        auto parentClass = eenv->getParent()->getVariable(parent).value;
        if(auto pc = std::dynamic_pointer_cast<Class>(parentClass)) {
            return pc->getMethod(name); 
        }
    }
    
    return nullptr;
}
};
/*
std::shared_ptr<Values::Runtime> Interpreter::IClass(std::shared_ptr<AST::ExprAST>& astNode, Environment& env) {
    AST::Class* Cluss = dynamic_cast<AST::Class*>(astNode.get());
    Environment classEnv;
    classEnv.setup();

    // Evaluate class body 
    for (auto& thing : Cluss->body) {
        this->evaluate(thing, classEnv);
    }

    // Create and store class
    auto clss = std::make_shared<Class>(classEnv, Cluss->name, Cluss->parent);
    env.setVariable(Cluss->name, clss, "class", true);

    return createNull();
}

std::shared_ptr<Values::Runtime> Interpreter::INew(std::shared_ptr<AST::ExprAST>& astNode, Environment& env) {
    AST::NewExpr* newExpr = dynamic_cast<AST::NewExpr*>(astNode.get());
    
    // Get the class
    auto classVar = env.getVariable(newExpr->className);
    if (!classVar.value || classVar.value->type() != "class") {
        throw std::runtime_error("Cannot instantiate non-class type: " + newExpr->className);
    }
    
    auto classObj = std::dynamic_pointer_cast<Class>(classVar.value);
    
    // Evaluate constructor arguments
    std::vector<std::shared_ptr<Values::Runtime>> args;
    for (auto& arg : newExpr->args) {
        args.push_back(this->evaluate(arg, env));
    }
    
    // Create instance by calling construct
    return classObj->construct(args);
}*/