#pragma once

struct RuntimeIDComponent {
    unsigned long long runtimeId;
};

struct ActorGameTypeComponent {
    enum GameType gameType;
};

struct ActorTypeComponent {
    uint8_t typeId;
};