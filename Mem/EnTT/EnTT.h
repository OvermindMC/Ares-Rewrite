#pragma once

#include <cstdint>

#include <entt/entity/entity.hpp>

enum class EntityId : std::uint32_t {};

template<>
struct entt::internal::entt_traits<EntityId> {
    using value_type = EntityId;

    using entity_type = std::uint32_t;
    using version_type = std::uint16_t;

    static constexpr entity_type entity_mask = 0x3FFFF;
    static constexpr entity_type version_mask = 0xFFF;
};

#undef max
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>