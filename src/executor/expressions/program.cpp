#include "../executor.hpp"

using NodeType = AST::NodeType;
using string = std::string;

std::unique_ptr<Values::Runtime> Interpreter::evaluateProgramRoot(const AST::ProgramRoot& node, Runtime::Environment& env) {
    std::unique_ptr<Values::Runtime> lastResult = std::make_unique<Values::Null>();
    for (const auto& expr : node.body) {
        lastResult = evaluateChild(expr, env);
    }
    return lastResult;
}