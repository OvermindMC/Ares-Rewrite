#include <Windows.h>

auto init(HINSTANCE hInstance) -> void {

    //

};

auto WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) -> BOOL {

    if(fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
    
    return 1;

};