#ifdef STD_CONSOLE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;

namespace Console {
    std::shared_ptr<Values::Runtime> out(FunctionCallback* callback){
        auto args = callback->parsedArgs;

        for(auto& arg : args){
            std::cout << arg->stringValue();
        }

        std::cout << "\n";

        return createNull();
    }
};
#endif