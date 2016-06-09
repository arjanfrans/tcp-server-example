cmake_minimum_required(VERSION 3.5.1)


## Required software
find_package(Boost REQUIRED COMPONENTS system)

## Sources and headers
include_directories(
    ${Boost_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

## Find all source files to be compiled into object files
file(GLOB_RECURSE SOURCES *.cc *.cpp)

## C++ compiler options
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14")

## -O0 = optimize for compilation time
## -03 = optimize for code size and execution time
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

## Source file containing the "main" function
set(MAIN_SOURCES main.cpp)
## Specify a name for the generated executable file
set(MAIN_EXE_NAME generic_executable)


## 1. Compile...
add_executable(
    ${MAIN_EXE_NAME}
    ${MAIN_SOURCES}
    # network/Session.cpp
    ${SOURCES}
)

## 2. Link...
target_link_libraries(
    ${MAIN_EXE_NAME}
    ${Boost_LIBRARIES}
)

## 3. Install...
install(
    TARGETS ${MAIN_EXE_NAME}
    RUNTIME DESTINATION bin
)

