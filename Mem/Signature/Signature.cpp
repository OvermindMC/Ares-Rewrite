#include "Signature.h"
#include "../../Utils/Debugger/Debugger.h"

auto Signature::get(SearchType type) -> void* {
    
    if(!this->searched) {

        auto parsed = hat::parse_signature(this->pattern);
        assert(parsed.has_value());

        auto result = hat::find_pattern(parsed.value(), ".text");
        
        this->searched = result.has_result();
        this->address = (this->searched ? (uintptr_t)result.get() : 0x0);

    };

    if(this->address) {
        auto offset = 0x0;

        switch(type) {
            case SearchType::Default:
                return (void*)this->address;
            break;

            case SearchType::VTable:
                offset = *(int*)(this->address + 0x3);
                return (void*)(uintptr_t**)((this->address + offset + 7));
            break;

            case SearchType::Ref:
                offset = *(int*)(this->address + 0x1);
                return (void*)(uintptr_t**)((this->address + offset + 5));
            break;
        };
    };

    return nullptr;

};