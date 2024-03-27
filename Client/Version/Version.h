#pragma once

#include <sstream>

class Version {
public:
    Version(int major_version, int minor_version, int patch_version) : major_ver(major_version), minor_ver(minor_version), patch_ver(patch_version) {};
public:
    auto get(void) -> std::string;
private:
    int major_ver, minor_ver, patch_ver;
};