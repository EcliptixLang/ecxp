#ifdef STD_MATH
#include "./math.hpp"

#define CAST(x) static_cast<Values::Number*>(x.get())->value()

namespace Math {
    std::unique_ptr<Values::Runtime> pow(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if(args[0]->type() != Values::Type::Number && args[3]->type() != Values::Type::Number){
            callback->Errorout("Cannot read a non number.");
        }

        return std::make_unique<Values::Number>(Values::Number(std::pow(CAST(args[0]), CAST(args[1]))));
    }
};
#endif