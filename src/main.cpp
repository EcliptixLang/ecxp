#include "parser/parser.hpp"
#include "executor/executor.hpp"
#include "std/console/asink.hpp"
#include "ast.hpp"
#include <iostream>

struct GlobalConfig {
    bool debug = false;
};

void setup(Runtime::Environment& env);

int main(int argc, char* argv[]){
    GlobalConfig conf;
    ArgumentParser args(argc, argv);

    if(args.getPositionalArgs().size() == 0)
        return -1;

    std::string file = Utilities::readFile(args.getPositionalArgs()[0]);

    Parser parser;
    std::shared_ptr<AST::ExprAST> prog = parser.produceAST(file);

    Interpreter irpr;
    Runtime::Environment env(nullptr);
    setup(env);
    Console::Async::start();
    irpr.evaluate(prog, env);
    Console::Async::stop();
    return 0;
}