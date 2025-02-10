#include "parser/parser.hpp"
#include "compiler/compiler.hpp"
#include "executor/executor.hpp"
#include "ast.hpp"
#include <iostream>

// temp

struct GlobalConfig {
    bool debug = false;
};

// temp

int main(int argc, char* argv[]){
    GlobalConfig conf;
    ArgumentParser args(argc, argv);

    if(args.getPositionalArgs().size() == 0)
        return -1;

    std::string file = Utilities::readFile(args.getPositionalArgs()[0]);

    Parser parser;
    std::shared_ptr<AST::ExprAST> prog = parser.produceAST(file);

    if(args.hasFlag("-c") || args.hasFlag("--compile")){
        Compiler compiler;
        compiler.compile(prog);
        compiler.save(args.getFlagValues("-o")[0]);
    } else {
        Interpreter irpr;
        Environment env;
        irpr.evaluate(prog, env);
    }

    return 0;
}