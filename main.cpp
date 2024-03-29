#include "Client/Client.h"

auto init(HINSTANCE hInstance) -> void {

    auto client = new Client("NetNode");
    client->init();

    auto sig = Mem::findSig("48 89 0D ? ? ? ? 48 89 0D ? ? ? ? 48 85 C0 74 0F 48 8B C8 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 09 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B 59 08 80 7B 19 00 75 4E 48 89 7C 24 ? 0F 1F 40 00 4C 8B 43 10 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B FB 48 8B 1B 48 8D 4F 20");

    std::ostringstream o;
    o << std::hex << MC::getClientInstance();
    Debugger::log(o.str());
    
    //
    Sleep(5000);

    delete client;
    Debugger::free();
    FreeLibraryAndExitThread(Mem::getDll(), 1);

};

auto WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) -> BOOL {

    if(fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
    
    return 1;

};