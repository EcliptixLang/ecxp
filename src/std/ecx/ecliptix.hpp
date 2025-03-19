#ifdef STD_ECLIPTIX
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>

using Values::Runtime;
using Values::FunctionCallback;

namespace Ecliptix {
    std::shared_ptr<Values::Runtime> exit(FunctionCallback* callback);
    std::shared_ptr<Values::Runtime> wait(FunctionCallback* callback);
};
#endif