#pragma once

#include "LevelRenderer/LevelRenderer.h"

class Level {
public:
    auto getEntityContextList(void) -> std::vector<struct EntityContext*>;
public:
    template<typename T>
    auto getEntityComponents(void) -> std::vector<T*>;
public:
    auto getRuntimeIds(void) -> std::vector<uint64_t>;
    auto getUniqueIds(void) -> std::vector<uint64_t>;
public:
    auto getEntities(void) -> std::vector<class Actor*>;
};