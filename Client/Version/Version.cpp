#include "Version.h"

auto Version::get(void) -> std::string {
    
    std::stringstream os;
    os << major_ver << "." << minor_ver << "." << patch_ver;

    return os.str();

};