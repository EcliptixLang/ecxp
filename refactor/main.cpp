#include "parser/parser.hpp"
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

    if(args.hasFlag("-q")){
        return 0;
    }
    Parser parser;
    std::shared_ptr<AST::Program> prog = parser.produceAST(file);

    return 0;
}