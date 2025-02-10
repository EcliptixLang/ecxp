#include "compiler.hpp"
#include <fstream>

void Compiler::save(std::string filename){
    std::fstream output(filename, std::ios::out);

    output.write(code.c_str(), code.size());

    output.close();
}