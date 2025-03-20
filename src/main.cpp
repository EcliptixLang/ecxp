#include "parser/parser.hpp"
#include "executor/executor.hpp"
#include "std/console/asink.hpp"
#include "ast.hpp"
#include <iostream>

struct GlobalConfig {
    bool debug = false;
};

void setup(Environment& env);

int main(int argc, char* argv[]){
    Console::Async::start();
//    GlobalConfig conf;
    ArgumentParser args(argc, argv);

    if(args.hasFlag("-h") || args.hasFlag( "--help")) {
        Console::Async::log("Usage: " + std::string(argv[0]) + " [files...]\n");
        Console::Async::log("Options:\n");
        Console::Async::log("  -h, --help    Show this help message\n");
        Console::Async::log("  -d, --debug   Enable debug mode\n");
        Console::Async::stop();
        return 0;
    }
    if(args.getPositionalArgs().size() == 0){
        Console::Async::log("\033[31mError\033[0m: \033[36mNo input files...\033[0m\n");
        Console::Async::stop();
        return 1;
    }
    Parser parser;
    Interpreter irpr;
    Environment env(nullptr);
    setup(env);

    for(auto& fil : args.getPositionalArgs()){
        std::string file = Utilities::readFile(fil);
        std::shared_ptr<AST::ExprAST> prog = parser.produceAST(file);
        irpr.evaluate(prog, env);
    }
    Console::Async::stop();
    return 0;
}