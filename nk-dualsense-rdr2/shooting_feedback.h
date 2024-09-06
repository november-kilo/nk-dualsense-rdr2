#pragma once

#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>

#include "../inc/types.h"

class shooting_feedback
{
public:
    static void init();
    static std::chrono::milliseconds get_milliseconds_to_wait(Hash weapon_hash);
    static unsigned char get_left_rumble();
    static unsigned char get_right_rumble();

private:
    static bool init_called_;

    static std::unordered_map<Hash, std::chrono::milliseconds> shooting_feedback_times_;
    static std::chrono::milliseconds default_milliseconds_to_wait_;

    static std::chrono::milliseconds get_or_default_feedback_ms(const std::string& property, long default_value);
    static void add_shooting_feedback_ms(const std::string& ammo_type, const std::chrono::milliseconds& feedback_time,
                                         std::unordered_map<Hash, std::chrono::milliseconds>& map);
    static std::vector<std::pair<std::string, std::chrono::milliseconds>> create_shooting_feedback_ms_array();
};
