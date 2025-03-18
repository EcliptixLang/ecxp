#include "../executor.hpp"
#include "../../fnvalues.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateFunctionCall(const AST::FunctionCallExpr& node, std::shared_ptr<Runtime::Environment> &env){
	std::vector<std::shared_ptr<Values::Runtime>> args{};
	for(auto& arg : node.arguments){
		args.push_back(this->evaluate(arg, env));
	}

	NodeType calleeType = node.callee->nodeType();
	if(calleeType == NodeType::MemberAccess){
		std::shared_ptr<Values::Runtime> value;
		std::shared_ptr<Values::Runtime> val = this->evaluate(node.callee, env);
			if(val->type() == "function"){
				Runtime::Environment enva(std::make_shared<Runtime::Environment>(env));
				Values::Function* fn = dynamic_cast<Values::Function*>(val.get());
				std::shared_ptr<Values::Runtime> value;

            	int i = 0;
            	for(auto& param : fn->parameters()){
            		if(args.size() >= i)
            			env->set(param, args[i], false);
            		else
            			env->set(param, std::make_shared<Values::Null>(Values::Null()), false);
            		i++;
            	}

            	for(auto& expr : fn->body()){
            		value = this->evaluate(expr, env);
            		if(value->type() == "return"){
            			Values::ReturnedValue* sum = dynamic_cast<Values::ReturnedValue*>(value.get());
            			if(sum->value()->type() == fn->type() || fn->type() == "auto")
            				return sum->value();
            			else {
            				std::cout << "Error while running function '" << fn->name() << "', it seems like it's requiring type '" << fn->type() << "' and the value it returned was of type '" << sum->value()->type() << "'.\n";
            				exit(6);
            			}	
            		}
            	}

            	if(fn->type() == "void" || fn->type() == "nothing")
            		return value;
            	else {
            		std::cout << "Error (INTERPRETER):\n- Error Code: 7\n- Error Description: No return in non void function\n- Function name: '" << fn->name() << "'\n- Required type: '" << fn->type() << "'\n";
            		exit(7);
            	}	

            	return value;
			} else if(val->type() == "native-fn"){
				Values::NativeFN* sym = dynamic_cast<Values::NativeFN*>(val.get());
				Values::FunctionCallback cb;
				cb.env = std::make_shared<Runtime::Environment>(env);
				cb.parsedArgs = args;
				return sym->call(&cb);
			}
			else
				throw std::runtime_error("Callee is not a function");
	}
	
	
	AST::IdentifierExpr* ident = dynamic_cast<AST::IdentifierExpr*>(node.callee.get());
	std::shared_ptr<Values::Runtime> fun = env->get(ident->name).value;
	if(fun->type() == "native-fn"){
		Values::NativeFN* fn = dynamic_cast<Values::NativeFN*>(fun.get());
		Values::FunctionCallback cb;
		cb.env = std::make_shared<Runtime::Environment>(env);
		cb.parsedArgs = args;
		
		return fn->call(&cb);
	} else if(fun->type() == "function"){
		Runtime::Environment enva(std::make_shared<Runtime::Environment>(env));
		AST::IdentifierExpr* ident = dynamic_cast<AST::IdentifierExpr*>(node.callee.get());
    	Runtime::Variable fun = env->get(ident->name);

    	Values::Function* fn = dynamic_cast<Values::Function*>(fun.value.get());
    	std::shared_ptr<Values::Runtime> value;

    	int i = 0;
    	for(auto& param : fn->parameters()){
    		if(args.size() >= i)
    			env->set(param, args[i], false);
    		i++;
    	}
    
    	for(auto& expr : fn->body()){
    		value = this->evaluate(expr, env);
    		if(value->type() == "return"){
    			Values::ReturnedValue* sum = dynamic_cast<Values::ReturnedValue*>(value.get());
    			if(sum->value()->type() == fn->type() || fn->type() == "auto")
    				return sum->value();
    			else {
    				std::cout << "Error while running function '" << fn->name() << "', it seems like it's requiring type '" << fn->type() << "' and the value it returned was of type '" << sum->value()->type() << "'.\n";
    				exit(6);
    			}	
    		}
    	}

    	if(fn->type() == "void" || fn->type() == "nothing")
    		return value;
    	else {
    		std::cout << "Error (INTERPRETER):\n- Error Code: 7\n- Error Description: No return in non void function\n- Function name: '" << fn->name() << "'\n- Required type: '" << fn->type() << "'\n";
    		exit(7);
    	}	

    	return value;
	}

	throw std::runtime_error("Non function is trying to get called.");
	
}