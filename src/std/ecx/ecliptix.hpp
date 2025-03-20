#ifdef STD_ECLIPTIX
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>

using Values::Runtime;
using Values::FunctionCallback;

namespace Ecliptix {
    std::unique_ptr<Values::Runtime> exit(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> wait(FunctionCallback* callback);
};
#endif