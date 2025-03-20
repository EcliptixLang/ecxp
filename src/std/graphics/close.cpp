#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
    std::unique_ptr<Values::Runtime> close(FunctionCallback* callback){
        CloseWindow();
        return createNull();
    }
};
#endif