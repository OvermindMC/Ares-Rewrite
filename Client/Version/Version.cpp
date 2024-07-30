#include "Version.h"

std::string Version::get() const {
    std::ostringstream os;
    os << major_ver << "." << minor_ver << "." << patch_ver;
    return os.str();
};

bool Version::operator>(const Version& other) const {
    if (major_ver > other.major_ver) return true;
    if (major_ver < other.major_ver) return false;
    if (minor_ver > other.minor_ver) return true;
    if (minor_ver < other.minor_ver) return false;
    return patch_ver > other.patch_ver;
};

bool Version::operator<(const Version& other) const {
    return !(*this > other) && !(*this == other);
};

bool Version::operator>=(const Version& other) const {
    return (*this > other) || (*this == other);
};

bool Version::operator<=(const Version& other) const {
    return (*this < other) || (*this == other);
};

bool Version::operator==(const Version& other) const {
    return major_ver == other.major_ver && minor_ver == other.minor_ver && patch_ver == other.patch_ver;
};

bool Version::operator!=(const Version& other) const {
    return !(*this == other);
};