#include "env.hpp"
#include "../fnvalues.hpp"
#include "../values.hpp"
#include <chrono>
#include <thread>
#include "utils.hpp"
#include "../executor/executor.hpp"
// #include <raylib/raylib.h>
#define _NORAYLIB

using NodeType = AST::NodeType; 
using string = std::string;
using Values::Null;
using Values::Number;
using Values::Boolean;
using Values::Object;
using Values::String;
using Values::FunctionCallback;
#define RuntimeVal std::shared_ptr<Values::Runtime>

template <typename T>
std::shared_ptr<T> createValue(T thing){
	return std::make_shared<T>(thing);
}

#ifndef _NORAYLIB
RuntimeVal ECLIPTIX_RunGameLoop(FunctionCallback* callback){
    Interpreter intr;
    if(callback->parsedArgs[0]->type() == "function")
        while(!WindowShouldClose()){
            BeginDrawing();

            for(auto& thing : dynamic_cast<Values::Function*>(callback->parsedArgs[0].get())->body){
                intr.evaluate(thing, *callback->env);
            }

            EndDrawing();
        }
    return createNull();
}

void ECLIPTIX_CustomLog(int msgType, const char *text, va_list args){}
void LogExit(std::string errorname, int exitCode = 0){
    std::cout << errorname << "\n";
    exit(exitCode);
}

RuntimeVal ECLIPTIX_ShowFPS(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if (!ValType(args[0], "Number") || !ValType(args[1], "Number")){
        LogExit(callback->name.append(" Errored out: one of its values is not a number.").c_str(), 1);
    }

    Number *a = switchNumber(args[0]);
    Number *b = switchNumber(args[1]);
    
    DrawFPS(a->value, b->value);

    return createNull();
}

RuntimeVal ECLIPTIX_Running(FunctionCallback* callback){
    return createValue<Boolean>(Boolean(!WindowShouldClose()));
}



RuntimeVal ECLIPTIX_CloseWindow(FunctionCallback* callback){
    CloseWindow();
    return createNull();
}

RuntimeVal ECLIPTIX_StartDrawing(FunctionCallback* callback){
    BeginDrawing();
    ClearBackground(BLACK);
    return createNull();
}

RuntimeVal ECLIPTIX_EndDrawing(FunctionCallback* callback){
    EndDrawing();
    return createNull();
}

RuntimeVal ECLIPTIX_DrawTriangle(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if (!ValType(args[0], "Object") || !ValType(args[1], "Object") || !ValType(args[2], "Object") || !ValType(args[3], "Object")){
        callback->Errorout(", one of its values is not an object.", 1);
    }

    Object *a = switchObject(args[0]);
    Object *b = switchObject(args[1]);
    Object *c = switchObject(args[2]);
    Object *d = switchObject(args[3]);

    if(hasNullObjects({"x", "y"}, a->props) 
        || hasNullObjects({"x", "y"}, b->props) 
        || hasNullObjects({"x", "y"}, c->props)
        || hasNullObjects({"r", "g", "b"}, d->props)
        ) { 
        callback->Errorout("One of the objects given are null.");
    }

    if(!ValType(a->props["x"], "Number") || !ValType(a->props["y"], "Number") 
        || !ValType(b->props["x"], "Number") || !ValType(b->props["y"], "Number") 
        || !ValType(c->props["x"], "Number") || !ValType(c->props["y"], "Number")
        || !ValType(d->props["r"], "Number") || !ValType(d->props["g"], "Number") || !ValType(d->props["b"], "Number")
        ) {
        LogExit("drawTriangle(o1, o2, o3, c) Errored out: a point on c is is not a number.", 1);
    }

    Number *a1 = switchNumber(a->props["x"]);
    Number *b1 = switchNumber(a->props["y"]);
    Number *a2 = switchNumber(b->props["x"]);
    Number *b2 = switchNumber(b->props["y"]);
    Number *a3 = switchNumber(c->props["x"]);
    Number *b3 = switchNumber(c->props["y"]);
    Number *ac = switchNumber(d->props["r"]);
    Number *bc = switchNumber(d->props["g"]);
    Number *cc = switchNumber(d->props["b"]);

    Vector2 v1 = { (float)a1->value, (float)b1->value };
    Vector2 v2 = { (float)a2->value, (float)b2->value };
    Vector2 v3 = { (float)a3->value, (float)b3->value };
    Color c1 = { (unsigned char)ac->value, (unsigned char)bc->value, (unsigned char)cc->value, 255 };
    DrawTriangle(v1, v2, v3, c1);

    return createNull();
}

RuntimeVal ECLIPTIX_DrawRect(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if (!ValType(args[0], "Object") || !ValType(args[1], "Object")){
        callback->Errorout("one of its values is not an object.");
    }

    Object *a = switchObject(args[0]);
    Object *b = switchObject(args[1]);

    if(hasNullObjects({"x", "y", "width", "height"}, a->props)){
        callback->Errorout("Rectangle object is null (or is missing something*).\n rec: { x, y, width, height }");
    }
    if(hasNullObjects({"r", "g", "b"}, b->props)){
        callback->Errorout("Color of Rectangle is null (or badly formatted*).\n col: { r, g, b }");
    }

    if(!ValType(a->props["x"], "Number") 
        || !ValType(a->props["y"], "Number") 
        || !ValType(a->props["height"], "Number") 
        || !ValType(a->props["width"], "Number") 
        || !ValType(b->props["r"], "Number") 
        || !ValType(b->props["g"], "Number") 
        || !ValType(b->props["b"], "Number")
    ) {
        DisplayErrorMessageBox("drawRectangle(rec, col) Errored out: a point on col is is not a number.");
        exit(1);
    }

    Number *a1 = switchNumber(a->props["x"]);
    Number *b1 = switchNumber(a->props["y"]);
    Number *c1 = switchNumber(a->props["width"]);
    Number *d1 = switchNumber(a->props["height"]);
    Rectangle rec = { (float)a1->value, (float)b1->value, (float)c1->value, (float)d1->value };

    Number *ac = switchNumber(b->props["r"]);
    Number *bc = switchNumber(b->props["g"]);
    Number *cc = switchNumber(b->props["b"]);
    Color co = { (unsigned char)ac->value, (unsigned char)bc->value, (unsigned char)cc->value, 255 };
    DrawRectangleRec(rec, co);

    return createNull();
}

RuntimeVal ECLIPTIX_DrawRectRounded(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if (!ValType(args[0], "Object") || !ValType(args[1], "Object") || !ValType(args[2], "Number")){
        callback->Errorout("one of its values is not an object.");
    }

    Object *a = switchObject(args[0]);
    Object *b = switchObject(args[1]);
    Number *rou = switchNumber(args[2]);

    if(hasNullObjects({ "x", "y", "width", "height" }, a->props)){
        callback->Errorout("Rectangle object is null (or is missing something*).\n rec: { x, y, width, height }");
    }
    if(hasNullObjects({"r", "g", "b"}, b->props)){
        callback->Errorout("Color of Rectangle is null (or badly formatted*).\n col: { r, g, b }");
    }

    if(!ValType(a->props["x"], "Number") || !ValType(a->props["y"], "Number") 
        || !ValType(a->props["height"], "Number") || a->props["width"]->type() != "Number"){
        callback->Errorout("a point on rec is not a number.");
    }
    if(!ValType(b->props["r"], "Number") || !ValType(b->props["g"], "Number") || !ValType(b->props["b"], "Number")){
        callback->Errorout("a point on col is is not a number.");
    }

    Number *a1 = switchNumber(a->props["x"]);
    Number *b1 = switchNumber(a->props["y"]);
    Number *c1 = switchNumber(a->props["width"]);
    Number *d1 = switchNumber(a->props["height"]);
    Rectangle rec = { (float)a1->value, (float)b1->value, (float)c1->value, (float)d1->value };

    Number *ac = switchNumber(b->props["r"]);
    Number *bc = switchNumber(b->props["g"]);
    Number *cc = switchNumber(b->props["b"]);
    Color co = { (unsigned char)ac->value, (unsigned char)bc->value, (unsigned char)cc->value, 255 };
    DrawRectangleRounded(rec, rou->value, rou->value, co);

    return createNull();
}

RuntimeVal ECLIPTIX_CreateWindow(FunctionCallback* callback){
    SetTraceLogCallback(ECLIPTIX_CustomLog);
    InitWindow(800, 600, "Test");

    std::map<std::string, RuntimeVal> Window;
    std::map<std::string, RuntimeVal> Draw;
    std::map<std::string, RuntimeVal> Debug;
    Debug["showFPS"] = std::make_shared<NativeFN>(ECLIPTIX_ShowFPS);
    
    Draw["Triangle"] =  std::make_shared<NativeFN>(ECLIPTIX_DrawTriangle);
    Draw["Rectangle"] = std::make_shared<NativeFN>(ECLIPTIX_DrawRect);
    Draw["RectangleRounded"] =  std::make_shared<NativeFN>(ECLIPTIX_DrawRectRounded);
    
    Window["destroy"] = std::make_shared<NativeFN>(ECLIPTIX_CloseWindow);
    Window["draw"] = std::make_shared<Values::Object>(Draw);
    Window["debug"] = std::make_shared<Values::Object>(Debug);
    Window["running"] = std::make_shared<NativeFN>(ECLIPTIX_Running);
    Window["run"] = std::make_shared<NativeFN>(ECLIPTIX_RunGameLoop);

    return std::make_shared<Values::Object>(Window);
}
#endif

RuntimeVal ECLIPTIX_Log(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    std::string value = "";
    
    for(auto& arg : args){
        value.append(" ").append(arg->stringValue());
    }

    if(value[0] == ' '){
        value.erase(0, 1);
    }

    std::cout << value << "\n";

    return createNull();
}

RuntimeVal ECLIPTIX_LogNNL(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    std::string value = "";
    
    for(auto& arg : args){
        value.append(" ").append(arg->stringValue());
    }

    if(value[0] == ' '){
        value.erase(0, 1);
    }

    std::cout << value;

    return createNull();
}

RuntimeVal ECLIPTIX_Ask(FunctionCallback* callback){
    std::cout << callback->parsedArgs[0]->stringValue();
    
    std::string ans_s;
    
    int ans_n;

    if (callback->parsedArgs[1]->stringValue() == "Number")
        std::cin >> ans_n;
    else
        std::cin >> ans_s;
    
    if (callback->parsedArgs[1]->stringValue() == "Number")
        return createValue<Number>(Values::Number(ans_n));
    else
        return createValue<String>(Values::String(ans_s));
}

RuntimeVal ECLIPTIX_Throw(FunctionCallback* callback){
    std::cout << "Error:\n- Code: 8\n- Description: ";
    ECLIPTIX_Log(callback);
    exit(8);

    return createNull();
}

RuntimeVal ECLIPTIX_ReadFile(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if(ValType(args[0], nullptr)){
        std::cout << "Cannot read null\n";
        exit(6);
    }

    std::string filecont = Utilities::readFile(args[0]->stringValue());

    return createValue<String>(Values::String(filecont));
}

RuntimeVal ECLIPTIX_WriteFile(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if(!ValType(args[0], "String") && !ValType(args[1], "String")){
        std::cout << "Cannot read a non string\n";
        exit(6);
    }
    
    Utilities::writeFile(args[0]->stringValue(), args[1]->stringValue());

    return std::make_shared<Values::Null>(Values::Null());
}

RuntimeVal ECLIPTIX_Wait(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if(args[0]->type() != "Number"){
        std::cout << "Cannot read a non number\n";
        exit(6);
    }

    std::this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(switchNumber(args[0])->value())));

    return createNull();
}

RuntimeVal ECLIPTIX_Exit(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    if(args[0]->type() != "Number"){
        std::cout << "Cannot read a non number\n";
        exit(6);
    }

    exit(switchNumber(args[0])->value());
}

RuntimeVal ECLIPTIX_ErrLog(FunctionCallback* callback){
    auto args = callback->parsedArgs;
    std::string value = "";
    
    for(auto& arg : args){
        value.append(" ").append(arg->stringValue());
    }

    if(value[0] == ' '){
        value.erase(0, 1);
    }

    std::cerr << value << "\n";

    return createNull();
}

std::map<std::string, RuntimeVal> ErrorStuff;
std::map<std::string, RuntimeVal> ConsoleStuff;
std::map<std::string, RuntimeVal> FileStuff;
std::map<std::string, RuntimeVal> ProcessStuff;
std::map<std::string, RuntimeVal> ProjectStuff;

void setup(std::shared_ptr<Runtime::Environment>& env){
    ErrorStuff["throw"]      =  std::make_shared<Values::NativeFN>(ECLIPTIX_Throw);
    ErrorStuff["out"]        =  std::make_shared<Values::NativeFN>(ECLIPTIX_ErrLog);
	ConsoleStuff["out"]      =  std::make_shared<Values::NativeFN>(ECLIPTIX_Log);
    ConsoleStuff["ask"]      =  std::make_shared<Values::NativeFN>(ECLIPTIX_Ask);
	FileStuff["read"]        =  std::make_shared<Values::NativeFN>(ECLIPTIX_ReadFile);
    FileStuff["write"]       =  std::make_shared<Values::NativeFN>(ECLIPTIX_WriteFile);
    ProcessStuff["exit"]     =  std::make_shared<Values::NativeFN>(ECLIPTIX_Exit);
    ProcessStuff["wait"]     =  std::make_shared<Values::NativeFN>(ECLIPTIX_Wait);

	env->safe_set("error", std::make_shared<Values::Object>(Values::Object(ErrorStuff)));
	env->safe_set("console", std::make_shared<Values::Object>(Values::Object(ConsoleStuff)));
	env->safe_set("file", std::make_shared<Values::Object>(Values::Object(FileStuff)));
    env->safe_set("process", std::make_shared<Values::Object>(Values::Object(ProcessStuff)));
    #ifndef _NORAYLIB
        env->safe_set("Window", std::make_shared<NativeFN>(ECLIPTIX_CreateWindow));
    #endif
	env->safe_set("null", std::make_shared<Values::Null>(Values::Null()));
	env->safe_set("true", std::make_shared<Values::Boolean>(Values::Boolean(true)));
	env->safe_set("false", std::make_shared<Values::Boolean>(Values::Boolean(false)));
}