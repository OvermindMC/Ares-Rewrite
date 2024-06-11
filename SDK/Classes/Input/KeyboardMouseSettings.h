#pragma once

#include "../../../Utils/Utils.h"
#include "../../../Mem/Mem.h"

class MCKeyBind {
public:
    std::string name;
    std::vector<int> bindKey;
private:
    char pad[0x8];
};

class KeyboardMouseSettings {
public:
    BUILD_ACCESS(std::vector<MCKeyBind>, keyboard_type_0, 0x8);
public:
    int GetMCKey(std::string keyName) {
		const std::vector<MCKeyBind>& keybinds = this->keyboard_type_0;
		for (auto& bind : keybinds) {
			if (bind.name == keyName) {
				return (bind.bindKey.size() ? bind.bindKey[0] : 0);
			};
		};
		return 0;
	};
};