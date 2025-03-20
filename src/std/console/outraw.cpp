#ifdef STD_CONSOLE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;
using Values::Runtime;

namespace Console {
    std::unique_ptr<Values::Runtime> outraw(FunctionCallback* callback){
        auto args = std::move(callback->parsedArgs);
        std::string value = "";
    
        for(auto& arg : args){
            value.append(" ").append(arg->stringValue());
        }

        if(value[0] == ' '){
            value.erase(0, 1);
        }

        std::cout << value;

        return createNull();
    }
};
#endif