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

# Exclude CMakeFiles directory
list(FILTER Sources EXCLUDE REGEX "/CMakeFiles/")

add_executable(EcliptixPlus "${Sources}")