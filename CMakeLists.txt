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

list(FILTER Sources EXCLUDE REGEX "/CMakeFiles/")
list(FILTER Sources EXCLUDE REGEX "/src/main.cpp")

add_library(libecx STATIC ${Sources})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_executable(ecx "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" ${Sources})

target_link_libraries(ecx PRIVATE libecx)
