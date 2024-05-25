cmake_minimum_required(VERSION 3.20)
project(NetNode VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

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
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG master
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG f2c417435c021b6bd2e426ffd9d1fc116b804146
)
FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
        libhat
        GIT_REPOSITORY https://github.com/BasedInc/libhat
        GIT_TAG 37ee990ef49e07571e9a948f78cd597c84a639d9
)
FetchContent_MakeAvailable(libhat)

add_library(NetNode SHARED)
target_sources(NetNode PRIVATE main.cpp)

add_subdirectory(Client)
add_subdirectory(Utils)
add_subdirectory(Mem)
add_subdirectory(SDK)

#EnTT config values
add_compile_definitions(ENTT_SPARSE_PAGE=2048)
add_compile_definitions(ENTT_PACKED_PAGE=128)

target_link_libraries(NetNode PRIVATE minhook nlohmann_json EnTT::EnTT libhat)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})