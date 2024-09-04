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
    static std::chrono::milliseconds get_or_default(const std::string& property, long default_value);
    static std::chrono::milliseconds get_shooting_feedback_ms(Hash weapon_hash);

private:
    static bool init_called_;
    static std::unordered_map<Hash, std::chrono::milliseconds> shooting_feedback_times_;
    static std::chrono::milliseconds default_shooting_feedback_ms_;

    static std::chrono::milliseconds get_or_default_feedback_ms(const std::string& key, int default_value);
    static void add_shooting_feedback_ms(const std::string& ammo_type, const std::chrono::milliseconds& feedback_time,
                                       std::unordered_map<Hash, std::chrono::milliseconds>& map);
    static std::vector<std::pair<std::string, std::chrono::milliseconds>> create_shooting_feedback_ms_array();
};
