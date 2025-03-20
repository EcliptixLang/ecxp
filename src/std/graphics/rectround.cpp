#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
    std::unique_ptr<Values::Runtime> drawRectRounded(FunctionCallback* callback){
        auto& args = callback->parsedArgs;
        if (!ValType(args[0], "Object") || !ValType(args[1], "Object") || !ValType(args[2], Values::Type::Number)){
            callback->Errorout("one of its values is not an object.");
        }

        Values::Object *a = switchObject(args[0]);
        Values::Object *b = switchObject(args[1]);
        
        Rectangle rect;
        bool exists = Integrity(a->properties(), rect);
        if(!exists){
            callback->Errorout("Rectangle object is null (or is missing something*).\n rec: { x, y, width, height }");
        }
        Color col;
        exists = Integrity(b->properties(), col);
        if(!exists){
            callback->Errorout("Color of Rectangle is null (or badly formatted*).\n col: { r, g, b }");
        }
        
        Values::Number *rou = switchNumber(args[2]);
        DrawRectangleRounded(rect, rou->value(), 1, col);

        return createNull();
    }
};
#endif