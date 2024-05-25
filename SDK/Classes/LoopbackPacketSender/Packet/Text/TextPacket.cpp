#include "TextPacket.h"

TextPacket::TextPacket(std::string message_contents, std::string message_author, TextPacketType text_type) {

    std::memcpy(this, Packet::createPacket<PacketID::Text>().get(), sizeof(TextPacket));

    this->type = text_type;
    this->author = message_author;
    this->message = message_contents;

};