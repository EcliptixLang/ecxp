#ifdef STD_GRAPHICS
#include "graphics.hpp"

namespace Graphics {
    bool Integrity(std::map<std::string, std::shared_ptr<Values::Runtime>> map, Rectangle &rect){
        if(hasNullObjects({ "x", "y", "width", "height" }, map)){
            return false;
        }

        if(!ValType(map["x"], "int") || !ValType(map["y"], "int") 
            || !ValType(map["height"], "int") || map["width"]->type() != "int"){
            return false;
        }

        Number *a = switchNumber(map["x"]);
        Number *b = switchNumber(map["y"]);
        Number *c = switchNumber(map["width"]);
        Number *d = switchNumber(map["height"]);
        rect = { (float)a->value(), (float)b->value(), (float)c->value(), (float)d->value() };
        return true;
    }

    bool Integrity(std::map<std::string, std::shared_ptr<Values::Runtime>> map, Color &col){
        if(hasNullObjects({"r", "g", "b"}, map)){
            return false;
        }

        if(!ValType(map["r"], "int") || !ValType(map["g"], "int") || !ValType(map["b"], "int")){
            return false;
        }

        Number *a = switchNumber(map["r"]);
        Number *b = switchNumber(map["g"]);
        Number *c = switchNumber(map["b"]);
        col = { (unsigned char)a->value(), (unsigned char)b->value(), (unsigned char)c->value(), 255 };
        return true;
    }

    bool Integrity(std::map<std::string, std::shared_ptr<Values::Runtime>> map, Vector2 &vec){
        if(hasNullObjects({"x", "y"}, map)){
            return false;
        }

        if(!ValType(map["x"], "int") || !ValType(map["y"], "int")){
            return false;
        }

        Number *x = switchNumber(map["x"]);
        Number *y = switchNumber(map["y"]);
        vec = { (float)x->value(), (float)y->value() };
        return true;
    }
};
#endif