#include "ScreenController.h"

auto ScreenController::getName(void) -> std::string {

    std::string result;
    auto result_raw_ptr = Mem::getNestedPtr(((uintptr_t)(this) + 0x10), { 0x48, 0x0 }, true);

    if(result_raw_ptr == nullptr)
        return result;
    
    result = ((std::string*)((uintptr_t)(result_raw_ptr) + 0x28))->c_str();
    return result;

};