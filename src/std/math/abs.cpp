#ifdef STD_MATH
#include "./math.hpp"

namespace Math {
    std::unique_ptr<Values::Runtime> abs(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if(args[0]->type() != Values::Type::Number){
            callback->Errorout("Cannot read a non number.");
        }

        return std::make_unique<Values::Number>(Values::Number(std::abs(static_cast<Values::Number*>(args[0].get())->value())));
    }
};
#endif