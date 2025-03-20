#pragma once
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <string>
#include <memory>

namespace Console {
    namespace Async {
        void start();
        void stop();
        void log(const std::string& message);
    };
};