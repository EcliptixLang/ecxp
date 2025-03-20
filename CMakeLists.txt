cmake_minimum_required(VERSION 3.10)

project(EcliptixPlus)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS 
"${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/**/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/executor/**/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/executor/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/**/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/lexer/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/**/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/*.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_definitions( 
    -D STD_CONSOLE
#   -D STD_COLORS
    -D STD_ECLIPTIX
    -D STD_FILE
#   -D STD_GRAPHICS
   -D STD_MATH
)

list(FILTER Sources EXCLUDE REGEX "/CMakeFiles/")
list(FILTER Sources EXCLUDE REGEX "/src/main.cpp")

add_library(ecx STATIC ${Sources})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_executable(ecxp "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

target_link_libraries(ecxp PRIVATE ecx)