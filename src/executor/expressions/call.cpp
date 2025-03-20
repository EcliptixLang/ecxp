#include "../executor.hpp"
#include "../../fnvalues.hpp"

using NodeType = AST::NodeType;
using namespace Values;

std::unique_ptr<Values::Runtime> Interpreter::evaluateFunctionCall(const AST::FunctionCallExpr& node,
                                                          Environment& env) {
    std::vector<std::unique_ptr<Values::Runtime>> args;
    args.reserve(node.arguments.size());
    for (auto& arg : node.arguments) {
        args.push_back(this->evaluate(arg, env));
    }

    if (node.callee->nodeType() == NodeType::MemberAccess) {
        auto val = this->evaluate(node.callee, env);
        
        if (val->type() == Type::Function) {
            auto* fn = static_cast<Function*>(val.get());
            env.enter_scope();
            
            for (size_t i = 0; i < fn->parameters().size(); ++i) {
                auto arg = i < args.size() ? std::move(args[i]) : std::make_unique<Null>();
                env.set(fn->parameters()[i], std::move(arg));
            }

            std::unique_ptr<Values::Runtime> result;
            for (auto& expr : fn->body()) {
                result = this->evaluate(expr, env);
                
                if (result && result->type() == Type::ReturnedValue) {
                    auto* ret = static_cast<ReturnedValue*>(result.get());
                    if (ret->value()->stringType() != fn->returnType()) {
                        throw std::runtime_error("Return type mismatch in function " + fn->name());
                    }
                    env.leave_scope();
                    return ret->takeValue();
                }
            }
            env.leave_scope();            
            throw std::runtime_error("No return in non-void function " + fn->name());
        }
        else if (val->type() == Type::NativeFunction) {
            auto* native = static_cast<NativeFN*>(val.get());
			Values::FunctionCallback cb;
			cb.parsedArgs = std::move(args);
			cb.env = &env;
			cb.name = "nativeFN";
            return native->call(&cb);
        }
        throw std::runtime_error("Member is not callable");
    }

    auto* ident = static_cast<AST::IdentifierExpr*>(node.callee.get());
    auto *func = env.get(ident->name);
    
    if (func->type() == Type::NativeFunction) {
        NativeFN* native = static_cast<NativeFN*>(func);
        Values::FunctionCallback cb;
		cb.parsedArgs = std::move(args);
		cb.env = &env;
		cb.name = ident->name;
        return native->call(&cb);
    }
    
    if (func->type() == Type::Function) {
        Function* fn = static_cast<Function*>(func);
        env.enter_scope();
        
        for (size_t i = 0; i < fn->parameters().size(); ++i) {
            auto arg = i < args.size() ? std::move(args[i]) : std::make_unique<Null>();
            env.set(fn->parameters()[i], std::move(arg));
        }

        std::unique_ptr<Values::Runtime> result;
        for (auto& expr : fn->body()) {
            result = this->evaluate(expr, env);
            
            if (result && result->type() == Type::ReturnedValue) {
                auto* ret = static_cast<ReturnedValue*>(result.get());
                if (ret->value()->stringType() != fn->returnType()) {
                    throw std::runtime_error("Return type mismatch in function " + fn->name());
                }
                env.leave_scope();
                return ret->takeValue();
            }
        }
        env.leave_scope();
        throw std::runtime_error("No return in non-void function " + fn->name());
    }

    throw std::runtime_error("Attempt to call non-function entity");
}