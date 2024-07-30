#include "Debugger.h"

std::string Debugger::name = "";
bool Debugger::doneInit = false;

void Debugger::init(const std::string& display_name) {
    if(Debugger::doneInit)
        return;
    
    Debugger::name = display_name;

    if (AllocConsole()) {
        FILE* cFile;
        Debugger::doneInit = freopen_s(&cFile, "CONOUT$", "w", stdout) == 0;
    };
};

void Debugger::free() {
    if(!Debugger::doneInit)
        return;
    
    fclose(stdout);
    FreeConsole();
};

void Debugger::log(const std::string& message) {
    if(!Debugger::doneInit)
        return;
    
    printf("[%s] %s: %s\n", genStamp().c_str(), name.c_str(), message.c_str());
    fflush(stdout);
};

std::string Debugger::genStamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    std::string timestamp = oss.str();
    return timestamp;
};