#include "Client/Client.h"

void init() {
    Client* client = new Client("Ares", Version(4, 0, 0));
    
    delete client;
    FreeLibraryAndExitThread(Mem::getDll(), 1);
};

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {
    if(fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
    };
    return TRUE;
};