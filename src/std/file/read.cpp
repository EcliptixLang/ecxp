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
    std::unique_ptr<Values::Runtime> read(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if(!ValType(args[0], Values::Type::String)){
            std::cout << "Cannot read non string\n";
            exit(6);
        }

        std::string filecont = Utilities::readFile(args[0]->stringValue());

        return std::make_unique<String>(Values::String(filecont));
    }
};
#endif