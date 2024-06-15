#include "Client/Client.h"

auto init(HINSTANCE hInstance) -> void {

    auto client = new Client("Ares", Version("3.0.0"));
    client->init();

    delete client;
    Debugger::free();
    FreeLibraryAndExitThread(Mem::getDll(), 1);

};

auto WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) -> BOOL {

    if(fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
    
    return 1;

};