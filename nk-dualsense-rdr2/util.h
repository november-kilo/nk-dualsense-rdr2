#pragma once

#include <chrono>
#include <chrono>
#include <string>
#include <unordered_map>

#include "../inc/natives.h"
#include "../inc/types.h"

namespace time_util {
    std::chrono::milliseconds time_now();
}

namespace util {
    Hash get_hash(const std::string& key);
    template<typename T> T clamp(T value, T min, T max);
    template<typename T> unsigned char to_unsigned_char(T value);
}

template<typename T>
T util::clamp(const T value, const T min, const T max) {
    static_assert(std::is_arithmetic_v<T>, "Arithmetic type required");
    
    if (value < min) {
        return min;
    }
        
    if (value > max) {
        return max;
    }
        
    return value;
}

template <typename T>
unsigned char util::to_unsigned_char(T value) {
    static_assert(std::is_arithmetic_v<T>, "Arithmetic type required");
    return static_cast<unsigned char>(clamp(value, 0, 255));
}

namespace player_util {
    Hash get_ammo_type();
    Hash get_weapon();
    float get_weapon_degradation();
    bool is_shooting();
    bool is_weapon_gun();
    bool is_gun_silent();
}
