#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
std::unique_ptr<Values::Runtime> drawRect(FunctionCallback* callback){
    auto& args = callback->parsedArgs;
    if (!ValType(args[0], "Object") || !ValType(args[1], "Object")){
        callback->Errorout("one of its values is not an object.");
    }
    Values::Object *a = switchObject(args[0]);
    Values::Object *b = switchObject(args[1]);    
    
    Rectangle rec;
    bool exists = Integrity(a->properties(), rec);
    if(!exists){
        callback->Errorout("Rectangle object is null (or is missing something*).\n rec: { x, y, width, height }");
    }
    Color col;
    exists = Integrity(b->properties(), col);
    if(!exists){
        callback->Errorout("Color of Rectangle is null (or badly formatted*).\n col: { r, g, b }");
    }
    DrawRectangleRec(rec, col);
    
    return createNull();
}
};
#endif