#pragma once

#include <type_traits>
#include <cstddef>

template <typename F>
auto IIFE(F f) {
    return f();
};

template <class T>
struct remove_cvref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

template <typename Ret, typename Type>
Ret& direct_access(Type* type, size_t offset) {
    union {
        size_t raw;
        Type* source;
        Ret* target;
    } u;
    u.source = type;
    u.raw += offset;
    return *u.target;
};

#define DEF_FIELD_RW(type, name) \
    __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name) \
    DEF_FIELD_RW(type, name) \
    type get##name()

#define BUILD_ACCESS(type, name, offset) \
    DEF_FIELD_RW(type, name) \
    type get##name() const { return direct_access<type>(this, offset); } \
    void set##name(type v) const { direct_access<type>(this, offset) = v; }

#define PTR_ACCESS(type, name, raw_ptr) \
    __declspec(property(get = get##name)) type name; \
    type get##name() const { return this->raw_ptr; }


#define SAFE_DEL(PTR) \
    do { \
        if ((PTR) != nullptr) { \
            delete (PTR); \
            (PTR) = nullptr; \
        } \
    } while (0)