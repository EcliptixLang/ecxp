#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
    std::shared_ptr<Values::Runtime> running(FunctionCallback* callback){
        return std::make_shared<Values::Boolean>(Values::Boolean(!WindowShouldClose()));
    }
};
#endif