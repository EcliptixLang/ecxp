#include "../executor.hpp"

using NodeType = AST::NodeType;
using string = std::string;

std::shared_ptr<Values::Runtime> Interpreter::evaluateProgramRoot(const AST::ProgramRoot& node, std::shared_ptr<Runtime::Environment> &env) {
    std::shared_ptr<Values::Runtime> lastResult = std::make_shared<Values::Null>();
    for (const auto& expr : node.body) {
        lastResult = evaluateChild(expr, env);
    }
    return lastResult;
}