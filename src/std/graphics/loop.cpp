#ifdef STD_GRAPHICS
#include "graphics.hpp"
#include "../../executor/executor.hpp"

namespace Graphics {
    std::shared_ptr<Values::Runtime> loop(FunctionCallback* callback){
        Interpreter intr;
        if(callback->parsedArgs[0]->type() == "function")
            while(!WindowShouldClose()){
                BeginDrawing();

                for(auto& thing : dynamic_cast<Values::Function*>(callback->parsedArgs[0].get())->body()){
                    intr.evaluate(thing, *callback->env);
                }

                EndDrawing();
            }
        return createNull();
    }
};
#endif