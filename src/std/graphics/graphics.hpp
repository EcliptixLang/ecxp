#ifdef STD_GRAPHICS
#include "../../values.hpp"
#include "../../fnvalues.hpp"
#include <memory>
#include <map>
#include <raylib.h>

using Values::Runtime;
using Values::Number;
using Values::FunctionCallback;

namespace Graphics {
    bool Integrity(std::map<std::string, std::unique_ptr<Values::Runtime>> &map, Rectangle &rect);
    bool Integrity(std::map<std::string, std::unique_ptr<Values::Runtime>> &map, Color &col);
    bool Integrity(std::map<std::string, std::unique_ptr<Values::Runtime>> &map, Vector2 &vec);
    void log(int msgType, const char *text, va_list args);

    std::unique_ptr<Values::Runtime> loop(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> showFPS(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> running(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> close(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> drawTriangle(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> drawRectRounded(FunctionCallback* callback);
    std::unique_ptr<Values::Runtime> drawRect(FunctionCallback* callback);
};
#endif