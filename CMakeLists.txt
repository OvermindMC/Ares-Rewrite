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

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG 41aab920b083aa424ac1d27666ce287eeaff6ceb
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
        libhat
        GIT_REPOSITORY https://github.com/BasedInc/libhat
        GIT_TAG 37ee990ef49e07571e9a948f78cd597c84a639d9
)
FetchContent_MakeAvailable(libhat)

add_library(Ares SHARED)
target_sources(Ares PRIVATE main.cpp)

add_compile_definitions(ENTT_SPARSE_PAGE=2048)
add_compile_definitions(ENTT_PACKED_PAGE=128)

target_link_libraries(Ares PRIVATE minhook libhat EnTT::EnTT)

add_subdirectory(Client)
add_subdirectory(Utils)
add_subdirectory(Mem)
add_subdirectory(SDK)