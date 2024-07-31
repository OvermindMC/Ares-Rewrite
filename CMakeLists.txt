cmake_minimum_required(VERSION 3.20)
project(Ares VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

include(FetchContent)

FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG master
)
FetchContent_MakeAvailable(minhook)

add_library(Ares SHARED)
target_sources(Ares PRIVATE main.cpp)
target_link_libraries(Ares PRIVATE minhook)

add_subdirectory(Client)
add_subdirectory(Utils)
add_subdirectory(Mem)