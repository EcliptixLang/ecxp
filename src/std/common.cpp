#ifdef STD_CONSOLE
    #include "./console/console.hpp"
#endif
#ifdef STD_COLORS
    #include "./colors/colors.hpp"    
#endif
#ifdef STD_ECLIPTIX
    #include "./ecx/ecliptix.hpp"    
#endif
#ifdef STD_FILE
    #include "./file/file.hpp"    
#endif
#ifdef STD_GRAPHICS
    #include "./graphics/graphics.hpp"    
#endif
#ifdef STD_MATH
    #include "./math/math.hpp"
#endif

#include "../utilities/env.hpp"
#include "../utilities/utils.hpp"
#include "../executor/executor.hpp"

template <typename T>
std::shared_ptr<T> createValue(T thing){
	return std::make_shared<T>(thing);
}


void setup(std::shared_ptr<Runtime::Environment>& env){
    #ifdef STD_CONSOLE
        std::map<std::string, std::shared_ptr<Values::Runtime>> ConsoleStuff;
        ConsoleStuff["ask"]         =  std::make_shared<Values::NativeFN>(Console::ask);
        ConsoleStuff["error"]       =  std::make_shared<Values::NativeFN>(Console::error);
        ConsoleStuff["out"]         =  std::make_shared<Values::NativeFN>(Console::out);
        ConsoleStuff["outraw"]      =  std::make_shared<Values::NativeFN>(Console::outraw);
    	env->safe_set("console", std::make_shared<Values::Object>(Values::Object(ConsoleStuff)));
    #endif
    #ifdef STD_COLORS
        std::map<std::string, std::shared_ptr<Values::Runtime>> ColorStuff;
    #endif
    #ifdef STD_ECLIPTIX
        std::map<std::string, std::shared_ptr<Values::Runtime>> EcliptixStuff;
        EcliptixStuff["exit"]      =  std::make_shared<Values::NativeFN>(Ecliptix::exit);
        EcliptixStuff["wait"]      =  std::make_shared<Values::NativeFN>(Ecliptix::wait);
        env->safe_set("ecx", std::make_shared<Values::Object>(Values::Object(EcliptixStuff)));
    #endif
    #ifdef STD_FILE
        std::map<std::string, std::shared_ptr<Values::Runtime>> FileStuff;
        FileStuff["read"]        =  std::make_shared<Values::NativeFN>(File::read);
        FileStuff["write"]       =  std::make_shared<Values::NativeFN>(File::write);
        env->safe_set("file", std::make_shared<Values::Object>(Values::Object(FileStuff)));
    #endif
    #ifdef STD_GRAPHICS
        std::map<std::string, std::shared_ptr<Values::Runtime>> GraphicsStuff;
        GraphicsStuff["loop"]                   =  std::make_shared<Values::NativeFN>(Graphics::loop);
        GraphicsStuff["showFPS"]                =  std::make_shared<Values::NativeFN>(Graphics::showFPS);
        GraphicsStuff["running"]                =  std::make_shared<Values::NativeFN>(Graphics::running);
        GraphicsStuff["close"]                  =  std::make_shared<Values::NativeFN>(Graphics::close);
        GraphicsStuff["drawTriangle"]           =  std::make_shared<Values::NativeFN>(Graphics::drawTriangle);
        GraphicsStuff["drawRectRounded"]        =  std::make_shared<Values::NativeFN>(Graphics::drawRectRounded);
        GraphicsStuff["drawRect"]               =  std::make_shared<Values::NativeFN>(Graphics::drawRect);
        env->safe_set("graphics", std::make_shared<Values::Object>(Values::Object(GraphicsStuff)));
    #endif
    #ifdef STD_MATH
        std::map<std::string, std::shared_ptr<Values::Runtime>> MathStuff;
    #endif

	env->safe_set("null", std::make_shared<Values::Null>(Values::Null()));
	env->safe_set("true", std::make_shared<Values::Boolean>(Values::Boolean(true)));
	env->safe_set("false", std::make_shared<Values::Boolean>(Values::Boolean(false)));
}