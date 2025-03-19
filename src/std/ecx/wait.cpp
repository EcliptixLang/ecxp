#ifdef STD_ECLIPTIX
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include "../common.hpp"
#include "../../utilities/utils.hpp"
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

using Values::FunctionCallback;
using Values::Runtime;
using Values::String;

namespace Ecliptix {
    std::shared_ptr<Values::Runtime> wait(FunctionCallback* callback){
        auto args = callback->parsedArgs;
        if(args[0]->type() != "int"){
            std::cout << "Cannot read a non number\n";
            exit(6);
        }

        std::this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(switchNumber(args[0])->value())));

        return createNull();
    }
};
#endif