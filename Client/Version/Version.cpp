#include "Version.h"

auto Version::get(void) -> std::string {
    
    std::stringstream os;
    os << major_ver << "." << minor_ver << "." << patch_ver;

    return os.str();

};

auto Version::operator>(const Version& other) const -> bool {
    if (major_ver > other.major_ver) {
        return true;
    } else if (major_ver < other.major_ver) {
        return false;
    };

    if (minor_ver > other.minor_ver) {
        return true;
    } else if (minor_ver < other.minor_ver) {
        return false;
    };

    if (patch_ver > other.patch_ver) {
        return true;
    };

    return false;
};

auto Version::operator<(const Version& other) const -> bool {
    return !(*this > other) && !(*this == other);
};

auto Version::operator>=(const Version& other) const -> bool {
    return (*this > other) || (*this == other);
};

auto Version::operator<=(const Version& other) const -> bool {
    return (*this < other) || (*this == other);
};

auto Version::operator==(const Version& other) const -> bool {
    return major_ver == other.major_ver && minor_ver == other.minor_ver && patch_ver == other.patch_ver;
};

auto Version::operator!=(const Version& other) const -> bool {
    return !(*this == other);
};