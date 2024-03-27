#pragma once

#include <functional>
#include <mutex>
#include <map>

template<typename KeyType, typename ValType>
class MapRef {
private:
    std::map<KeyType, ValType>& map_;
    std::mutex& mutex_;
public:
    MapRef(std::map<KeyType, ValType>& map, std::mutex& mutex) : map_(map), mutex_(mutex) {
        std::lock_guard<std::mutex> lock(mutex_);
    };
    ~MapRef() = default;
public:
    auto size(void) -> size_t {
        return map_.size();
    };
    auto clear(void) -> void {
        return map_.clear();
    };
public:
    auto find(KeyType type) -> ValType {
        auto iter = map_.find(type);
        if (iter != map_.end())
            return iter->second;
        return ValType{};
    };
    auto contains(KeyType type) -> bool {
        return map_.find(type) != map_.end();
    };

    auto insert(KeyType type, ValType val) -> void {
        map_.emplace(type, val);
    };

    auto erase(KeyType type) -> void {
        auto iter = map_.find(type);
        if (iter != map_.end())
            map_.erase(iter);
    };

    auto forEach(std::function<void(KeyType, ValType, bool&)> func) -> void {
        for (const auto& pair : map_) {
            bool shouldContinue = true;
            
            if constexpr(std::is_pointer_v<ValType>) {
                if (!pair.second)
                    continue;
            };
            
            func(pair.first, pair.second, shouldContinue);
            
            if (!shouldContinue)
                break;
        };
    };
};