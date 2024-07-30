#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <Windows.h>

class Debugger {
public:
    static void init(const std::string&);
    static void free();

    static void log(const std::string&);
    static std::string genStamp();
private:
    static std::string name;
    static bool doneInit;
};