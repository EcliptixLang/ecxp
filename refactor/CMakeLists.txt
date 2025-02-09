cmake_minimum_required(VERSION 3.10)

project(EcliptixPlus)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/compiler/**/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/compiler/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/executor/**/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/executor/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/lexer/**/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/lexer/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/parser/**/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/utilities/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Exclude CMakeFiles directory
list(FILTER Sources EXCLUDE REGEX "/CMakeFiles/")

add_executable(EcliptixPlus "${Sources}")