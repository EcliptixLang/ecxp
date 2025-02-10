#include "env.hpp"
#include "../fnvalues.hpp"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
    #include <winutils.hpp>
#else
    #include <unistd.h>
#endif

#include "utils.hpp"

Environment* Environment::getParent(){
    return parent;
}

int Environment::variableCount(){
    return variables.size();
}

void Environment::setParent(Environment* Parent){
    parent = Parent;
}

Variable Environment::getVariable(const std::string& varname){
    for(auto& var: variables){
        if(var.name == varname)
            return Variable {
                .name = var.name,
                .value = var.value->clone(),
                .constant = var.constant,
            };
    }

    if(!parent){
        std::cout << "Variable " << varname << " undefined, parent count: " << parentCount() << "\n";
        exit(1);
    }

    return parent->getVariable(varname);
}

int Environment::parentCount(int num){
    num++;
    if(!parent)
        return num;

    return parent->parentCount(num);
}

void Environment::setVariable(const std::string& varname, std::shared_ptr<Values::Runtime> vallo, std::string type, bool constant){
    for (auto& var : variables) {
        if (var.name == varname) {
            if (var.constant) {
                std::cout << "Cannot modify a constant variable.\n";
                return;
            }
            var.value = vallo->clone();
            return;
        }
    }
    variables.push_back({ varname, vallo, constant, type });
}

void Environment::setVariableSafe(const std::string& varname, std::shared_ptr<Values::Runtime> vallo, bool constant){
    for (auto& var : variables) {
        if (var.name == varname) {
            if (var.constant) {
                return;
            }
            var.value = vallo->clone();
            return;
        }
    }
    
    if(!parent)
        return variables.push_back({ varname, vallo, constant });
    
    return parent->setVariableSafe(varname, vallo, constant);
}

std::vector<Variable> Environment::getVariables(){
    return variables;
}