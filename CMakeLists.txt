cmake_minimum_required(VERSION 3.20)
project(NetNode VERSION 1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG master
)
FetchContent_MakeAvailable(minhook)

add_library(NetNode SHARED)
target_sources(NetNode PRIVATE main.cpp)
target_link_libraries(NetNode PRIVATE minhook)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})