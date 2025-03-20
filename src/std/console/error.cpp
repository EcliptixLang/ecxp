#ifdef STD_CONSOLE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;

namespace Console {
    std::unique_ptr<Values::Runtime> error(FunctionCallback* callback){
        auto& args = callback->parsedArgs;

        for(auto& arg : args){
            std::cerr << arg->stringValue();
        }

        std::cerr << "\n";

        return createNull();
    }
};
#endif