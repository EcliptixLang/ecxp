#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
    std::unique_ptr<Values::Runtime> drawTriangle(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if (!ValType(args[0], "Object") || !ValType(args[1], "Object") || !ValType(args[2], "Object") || !ValType(args[3], "Object")){
            callback->Errorout(", one of its values is not an object.", 1);
        }

        Values::Object *a = switchObject(args[0]);
        Values::Object *b = switchObject(args[1]);
        Values::Object *c = switchObject(args[2]);
        Values::Object *d = switchObject(args[3]);

        Vector2 v1;
        bool exists = Integrity(a->properties(), v1);
        if(!exists){
            callback->Errorout("Vector2 object is null (or is missing something*).\n vec: { x, y }", 1);
        }
        Vector2 v2;
        exists = Integrity(b->properties(), v2);
        if(!exists){
            callback->Errorout("Vector2 object is null (or is missing something*).\n vec: { x, y }", 1);
        }
        Vector2 v3;
        exists = Integrity(a->properties(), v3);
        if(!exists){
            callback->Errorout("Vector2 object is null (or is missing something*).\n vec: { x, y }", 1);
        }
        Color c1;
        exists = Integrity(d->properties(), c1);
        if(!exists){
            callback->Errorout("Vector2 object is null (or is missing something*).\n vec: { x, y }", 1);
        }

        DrawTriangle(v1, v2, v3, c1);

        return createNull();
    }
};
#endif