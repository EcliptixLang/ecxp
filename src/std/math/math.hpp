#ifdef STD_MATH
#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>
#include <cmath>

using Values::Runtime;
using Values::FunctionCallback;

namespace Math {
    std::unique_ptr<Values::Runtime> abs(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> min(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> max(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> round(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> sqrt(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> pow(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> log(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> sin(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> cos(FunctionCallback* callback);
};
#endif