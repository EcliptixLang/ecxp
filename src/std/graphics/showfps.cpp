#ifdef STD_GRAPHICS
#include "graphics.hpp"
#include "../../executor/executor.hpp"

namespace Graphics {
    std::unique_ptr<Values::Runtime> showFPS(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if (!ValType(args[0], Values::Type::Number) || !ValType(args[1], Values::Type::Number)){
            callback->Errorout("one of its values is not a number.");
        }

        Number *a = switchNumber(args[0]);
        Number *b = switchNumber(args[1]);

        DrawFPS(a->value(), b->value());

        return createNull();
    }
};
#endif