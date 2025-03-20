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


void setup(Runtime::Environment& env){
    #ifdef STD_CONSOLE
        std::map<std::string, std::unique_ptr<Values::Runtime>> ConsoleStuff;
        ConsoleStuff["ask"]         =  std::make_unique<Values::NativeFN>(Console::ask);
        ConsoleStuff["error"]       =  std::make_unique<Values::NativeFN>(Console::error);
        ConsoleStuff["out"]         =  std::make_unique<Values::NativeFN>(Console::out);
        ConsoleStuff["outraw"]      =  std::make_unique<Values::NativeFN>(Console::outraw);
    	env.set("console", std::make_unique<Values::Object>(std::move(ConsoleStuff)));
    #endif
    #ifdef STD_COLORS
        std::map<std::string, std::unique_ptr<Values::Runtime>> ColorStuff;
    #endif
    #ifdef STD_ECLIPTIX
        std::map<std::string, std::unique_ptr<Values::Runtime>> EcliptixStuff;
        EcliptixStuff["exit"]      =  std::make_unique<Values::NativeFN>(Ecliptix::exit);
        EcliptixStuff["wait"]      =  std::make_unique<Values::NativeFN>(Ecliptix::wait);
        env.set("ecx", std::make_unique<Values::Object>(std::move(EcliptixStuff)));
    #endif
    #ifdef STD_FILE
        std::map<std::string, std::unique_ptr<Values::Runtime>> FileStuff;
        FileStuff["read"]        =  std::make_unique<Values::NativeFN>(File::read);
        FileStuff["write"]       =  std::make_unique<Values::NativeFN>(File::write);
        env.set("file", std::make_unique<Values::Object>(std::move(FileStuff)));
    #endif
    #ifdef STD_GRAPHICS
        std::map<std::string, std::unique_ptr<Values::Runtime>> GraphicsStuff;
        GraphicsStuff["loop"]                   =  std::make_unique<Values::NativeFN>(Graphics::loop);
        GraphicsStuff["showFPS"]                =  std::make_unique<Values::NativeFN>(Graphics::showFPS);
        GraphicsStuff["running"]                =  std::make_unique<Values::NativeFN>(Graphics::running);
        GraphicsStuff["close"]                  =  std::make_unique<Values::NativeFN>(Graphics::close);
        GraphicsStuff["drawTriangle"]           =  std::make_unique<Values::NativeFN>(Graphics::drawTriangle);
        GraphicsStuff["drawRectRounded"]        =  std::make_unique<Values::NativeFN>(Graphics::drawRectRounded);
        GraphicsStuff["drawRect"]               =  std::make_unique<Values::NativeFN>(Graphics::drawRect);
        env.set("graphics", std::make_unique<Values::Object>(std::move(GraphicsStuff)));
    #endif
    #ifdef STD_MATH
        std::map<std::string, std::unique_ptr<Values::Runtime>> MathStuff;
        MathStuff["abs"] = std::make_unique<Values::NativeFN>(Math::abs);
        MathStuff["min"] = std::make_unique<Values::NativeFN>(Math::min);
        MathStuff["max"] = std::make_unique<Values::NativeFN>(Math::max);
        MathStuff["round"] = std::make_unique<Values::NativeFN>(Math::round);
        MathStuff["sqrt"] = std::make_unique<Values::NativeFN>(Math::sqrt);
        MathStuff["pow"] = std::make_unique<Values::NativeFN>(Math::pow);
        MathStuff["log"] = std::make_unique<Values::NativeFN>(Math::log);
        MathStuff["sin"] = std::make_unique<Values::NativeFN>(Math::sin);
        MathStuff["cos"] = std::make_unique<Values::NativeFN>(Math::cos);
        env.set("math", std::make_unique<Values::Object>(std::move(MathStuff)));
    #endif

	env.set("null", std::make_unique<Values::Null>());
	env.set("true", std::make_unique<Values::Boolean>(std::move(true)));
	env.set("false", std::make_unique<Values::Boolean>(std::move(false)));
}