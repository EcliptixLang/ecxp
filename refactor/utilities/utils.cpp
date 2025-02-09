#include "utils.hpp"
#include <fstream>
#include <sstream>

namespace Utilities {
    std::string readFile(std::string name) {
       std::ifstream file(name);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + name);
        }

        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void writeFile(std::string name, std::string value) {
       std::ofstream file(name);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + name);
        }

        file.write(value.c_str(), value.size());
    }

    CharArr split(std::string src) {
        CharArr st{};
        for (char ch : src) {
            st.push_back(ch);
        }
        return st;
    }
}


#include "../ast.hpp"

namespace AST {
    std::string stringifyAST(Nodes type){
        switch(type){
            case Nodes::Number: return "number";
            case Nodes::Array: return "array";
            case Nodes::Assignment: return "assignment";
            case Nodes::Binary: return "binary";
            case Nodes::Call: return "call";
            case Nodes::Element: return "element";
            case Nodes::Equality: return "equality";
            case Nodes::Function: return "function";
            case Nodes::Identifier: return "identifier";
            case Nodes::If: return "if";
            case Nodes::Member: return "member";
            case Nodes::Object: return "object";
            case Nodes::Program: return "program";
            case Nodes::ShellCmd: return "shell";
            case Nodes::String: return "string";
            case Nodes::Variable: return "variable";
            case Nodes::When: return "when";
            case Nodes::While: return "while";
            case Nodes::Skip: return "skip";
            case Nodes::Return: return "return";
            case Nodes::Break: return "break";
            case Nodes::Class: return "class";
            default: return "unknown";
        }
    }
}