#ifdef STD_CONSOLE
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>
#include <thread>

namespace Console {
    namespace Async {
        void start();
        void stop();
    };
    std::unique_ptr<Values::Runtime> ask(Values::FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> error(Values::FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> out(Values::FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> outraw(Values::FunctionCallback* callback);
};
#endif