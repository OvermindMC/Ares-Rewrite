#pragma once

#include <random>

template<typename T>
class Random {
private:
    T _min, _max, _result;
public:
    Random(T min, T max) : _min(min), _max(max) {
        this->gen();
    };

    T operator()() {
        return this->_result;
    };

    auto setMin(T min) -> void {
        this->updateRange(min, this->_max);
    };

    auto setMax(T max) -> void {
        this->updateRange(this->_min, max);
    };
public:
    auto gen() -> Random<T>& {
        std::random_device rd;
        std::mt19937 gen(rd());

        using DistributionType = typename std::conditional<std::is_floating_point<T>::value, std::uniform_real_distribution<T>, std::uniform_int_distribution<T>>::type;
        DistributionType dist(_min, _max);
        this->_result = dist(gen);

        return *this;
    };
private:
    auto updateRange(T min, T max) -> void {
        this->_min = min;
        this->_max = max;
        this->gen();
    };
};