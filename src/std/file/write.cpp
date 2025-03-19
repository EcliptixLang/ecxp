#ifdef STD_FILE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include "../common.hpp"
#include "../../utilities/utils.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;
using Values::Runtime;
using Values::String;

namespace File {
    std::shared_ptr<Values::Runtime> write(FunctionCallback* callback){
        auto args = callback->parsedArgs;
        if(!ValType(args[0], "char*") && !ValType(args[1], "char*")){
            std::cout << "Cannot read a non string\n";
            exit(6);
        }

        Utilities::writeFile(args[0]->stringValue(), args[1]->stringValue());

        return createNull();
    }
};
#endif