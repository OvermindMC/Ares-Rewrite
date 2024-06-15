#pragma once

#include <sstream>

class Version {
public:
    Version(int major_version, int minor_version, int patch_version) : major_ver(major_version), minor_ver(minor_version), patch_ver(patch_version) {};
    Version(const std::string& version_str) {
        std::istringstream iss(version_str);
        char dot;

        iss >> major_ver >> dot >> minor_ver >> dot >> patch_ver;
    };
public:
    auto get(void) -> std::string;

    auto operator>(const Version& other) const -> bool;
    auto operator<(const Version& other) const -> bool;
    auto operator>=(const Version& other) const -> bool;
    auto operator<=(const Version& other) const -> bool;
    auto operator==(const Version& other) const -> bool;
    auto operator!=(const Version& other) const -> bool;
private:
    int major_ver, minor_ver, patch_ver;
};