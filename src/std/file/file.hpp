#ifdef STD_FILE
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>

using Values::Runtime;
using Values::FunctionCallback;

namespace File {
    std::unique_ptr<Values::Runtime> read(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> write(FunctionCallback* callback);
};
#endif