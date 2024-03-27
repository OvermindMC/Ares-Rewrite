#pragma once

#include <filesystem>
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cstdio>
#include <string>
#include <ctime>

class Debugger {
private:
    static std::string name;
    static bool initialized;
public:
    static auto init(std::string) -> void;
    static auto free() -> void;
public:
    static auto log(const std::string& message) -> void;
    static auto genStamp() -> std::string;
public:
    static auto clear() -> void;
};