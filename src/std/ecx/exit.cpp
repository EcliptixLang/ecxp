#ifdef STD_ECLIPTIX
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;

namespace Ecliptix {
        std::shared_ptr<Values::Runtime> exit(FunctionCallback* callback){
        auto args = callback->parsedArgs;
        if(args[0]->type() != "int"){
            std::cout << "Cannot read a non number\n";
            ::exit(6);
        }

        ::exit(switchNumber(args[0])->value());
    }
};
#endif