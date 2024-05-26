#pragma once

#include "../Packet.h"

class TextPacket : public Packet {
private:
    char pad[0xD0];
public:
    enum class TextPacketType : int { RAW = 0, CHAT = 1, TRANSLATION = 2, POPUP = 3, JUKEBOX_POPUP = 4, TIP = 5, SYSTEM = 6, WHISPER = 7, ANNOUNCEMENT = 8, JSON_WHISPER = 9, JSON = 10, JSON_ANNOUNCEMENT = 11 };
public:
    BUILD_ACCESS(TextPacketType, type, 0x30);
public:
    BUILD_ACCESS(std::string, author, 0x38);
    BUILD_ACCESS(std::string, message, 0x58);
public:
    BUILD_ACCESS(bool, needsTranslate, 0x78);
public:
    BUILD_ACCESS(std::string, xuid, 0x98);
    BUILD_ACCESS(std::string, platformChatId, 0xB8);
};