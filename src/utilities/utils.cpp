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
    std::string stringifyAST(NodeType type){
        switch(type){
            case NodeType::NumberLiteral: return "int";
            case NodeType::ArrayLiteral: return "array";
            case NodeType::AssignmentExpr: return "assignment";
            case NodeType::BinaryOperation: return "binary";
            case NodeType::FunctionCall: return "call";
            case NodeType::ObjectProperty: return "element";
            case NodeType::EqualityCheck: return "equality";
            case NodeType::FunctionDeclaration: return "function";
            case NodeType::IdentifierExpr: return "identifier";
            case NodeType::IfStatement: return "if";
            case NodeType::MemberAccess: return "member";
            case NodeType::ObjectLiteral: return "Object";
            case NodeType::ProgramRoot: return "program";
            case NodeType::ShellCommand: return "shell";
            case NodeType::StringLiteral: return "char*";
            case NodeType::VariableDeclaration: return "variable";
            case NodeType::WhenStatement: return "when";
            case NodeType::WhileLoop: return "while";
            case NodeType::SkipStatement: return "skip";
            case NodeType::ReturnStatement: return "return";
            case NodeType::BreakStatement: return "break";
            default: return "unknown";
        }
    }
}