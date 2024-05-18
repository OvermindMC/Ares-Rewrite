#include "ScreenController.h"

auto ScreenController::getName(void) -> std::string {

    std::string result;
    auto result_raw_ptr = Mem::getNestedPtr(((unsigned long long)(this) + 0x10), { 0x48, 0x0 }, true);

    if(result_raw_ptr == nullptr)
        return result;
    
    result = ((std::string*)((unsigned long long)(result_raw_ptr) + 0x28))->c_str();
    return result;

};

auto ScreenController::closeScreen(void) -> void {

    return Mem::callVFunc<12, void>(this);

};

auto ScreenController::handleDropItem(std::string container, int slot) -> void {

    using Func = void (__thiscall*)(ScreenController*, const std::string&, int, int*);
    static auto _Func = (Func)(Mem::findSig("48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 4D 8B F1 45 8B F8")->get(Signature::SearchType::Default));

    if(_Func) {
        int stack[6]{};
        
        for (int i = 0; i < 6; i++)
            stack[i] = 0;
        
        stack[0] = 1;
        return _Func(this, container, slot, stack);
    };

};

auto ScreenController::handleAutoPlace(std::string container, int slot) -> void {

    using Func = void (__thiscall*)(ScreenController*, unsigned long long, const std::string&, int);
    static auto _Func = (Func)(Mem::findSig("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B ? ? ? F0")->get(Signature::SearchType::Default));

    if(_Func) {
        return _Func(this, 0x7FFFFFFF, container, slot);
    };

};

auto ScreenController::getSelectedSlot(std::string container, int slot) -> ItemStack* {

    return Mem::callVFunc<62, ItemStack*, const std::string&, int>(this, container, slot);

};