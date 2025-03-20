#include "../executor.hpp"

using NodeType = AST::NodeType; 
using string = std::string;

bool troti(Values::Runtime* conditional) {
    switch (conditional->type()) {
        case Values::Type::Boolean: {
            bool val = static_cast<Values::Boolean*>(conditional)->value();
            return val;
        }
        case Values::Type::Number: {
            return static_cast<Values::Number*>(conditional)->value() != 0;
        }
        default: return conditional != nullptr;
    }
}

std::unique_ptr<Values::Runtime> Interpreter::evaluateWhileLoop(
    const AST::WhileLoop& node, 
    Runtime::Environment& env
) {
    while (true) {
        auto cond = evaluate(node.condition, env);
        
        if (!troti(cond.get())) break;
        env.enter_scope();        

        const auto& body = node.body;
        
        auto end_it = body.end();
        for (auto it = body.begin(); it != end_it; ++it) {
            auto result = evaluate(*it, env);

            if (result && result->type() == Values::Type::Break) {
                env.leave_scope();
                return std::make_unique<Values::Null>();
            }
        }
        env.leave_scope();
    }
    return std::make_unique<Values::Null>();
}