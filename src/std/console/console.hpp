#ifdef STD_CONSOLE
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>

using Values::Runtime;
using Values::FunctionCallback;

namespace Console {
    std::shared_ptr<Values::Runtime> ask(FunctionCallback* callback);
    std::shared_ptr<Values::Runtime> error(FunctionCallback* callback);
    std::shared_ptr<Values::Runtime> out(FunctionCallback* callback);
    std::shared_ptr<Values::Runtime> outraw(FunctionCallback* callback);
};
#endif