#ifdef STD_CONSOLE
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include "../common.hpp"
#include <string>
#include <iostream>

using Values::FunctionCallback;
using Values::String;
using Values::Number;

namespace Console {
    std::shared_ptr<Values::Runtime> ask(FunctionCallback* callback){
        std::cout << callback->parsedArgs[0]->stringValue();

        std::string ans_s;
        double ans_n;

        if (callback->parsedArgs[1]->stringValue() == "int")
            std::cin >> ans_n;
        else
            std::cin >> ans_s;

        if (callback->parsedArgs[1]->stringValue() == "int")
            return std::make_shared<Number>(Values::Number(ans_n));
        else
            return std::make_shared<String>(Values::String(ans_s));
    }
}
#endif