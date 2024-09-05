#include "shooting_feedback.h"

#include "console.h"
#include "properties.h"
#include "util.h"

bool shooting_feedback::init_called_ = false;
std::chrono::milliseconds shooting_feedback::default_shooting_feedback_ms_ = std::chrono::milliseconds(100);
std::unordered_map<Hash, std::chrono::milliseconds> shooting_feedback::shooting_feedback_times_;

void shooting_feedback::init() {
    auto ammo_types = create_shooting_feedback_ms_array();

    for (const auto& [ammo_type, feedback_time] : ammo_types) {
        add_shooting_feedback_ms(ammo_type, feedback_time, shooting_feedback_times_);
    }

    init_called_ = true;
}

std::chrono::milliseconds shooting_feedback::get_shooting_feedback_ms(const Hash weapon_hash) {
    if (!init_called_) {
        init();
    }
    
    if (const auto iter = shooting_feedback_times_.find(weapon_hash); iter != shooting_feedback_times_.end()) {
        return iter->second;
    }

    return default_shooting_feedback_ms_;
}

void shooting_feedback::add_shooting_feedback_ms(const std::string& ammo_type,
                                                 const std::chrono::milliseconds& feedback_time,
                                                 std::unordered_map<Hash, std::chrono::milliseconds>& map) {
    map[util::get_hash(ammo_type)] = feedback_time;
}

std::chrono::milliseconds shooting_feedback::get_or_default_feedback_ms(const std::string& property, const long default_value) {
    const prop_value value = properties::get_instance().get(property, prop_value{default_value});
    return std::chrono::milliseconds{std::get<long>(value)};
}

std::vector<std::pair<std::string, std::chrono::milliseconds>> shooting_feedback::create_shooting_feedback_ms_array() {
 std::vector<std::pair<std::string, std::chrono::milliseconds>> feedbacks {
        {"AMMO_PISTOL", get_or_default_feedback_ms("pistol_feedback_ms", 100)},
        {"AMMO_PISTOL_EXPRESS", get_or_default_feedback_ms("pistol_express_feedback_ms", 110)},
        {"AMMO_PISTOL_EXPRESS_EXPLOSIVE", get_or_default_feedback_ms("pistol_express_explosive_feedback_ms", 200)},
        {"AMMO_PISTOL_HIGH_VELOCITY", get_or_default_feedback_ms("pistol_high_velocity_feedback_ms", 110)},
        {"AMMO_PISTOL_SPLIT_POINT", get_or_default_feedback_ms("pistol_split_point_feedback_ms", 110)},
        {"AMMO_REPEATER", get_or_default_feedback_ms("repeater_feedback_ms", 200)},
        {"AMMO_REPEATER_EXPRESS", get_or_default_feedback_ms("repeater_express_feedback_ms", 220)},
        {"AMMO_REPEATER_EXPRESS_EXPLOSIVE", get_or_default_feedback_ms("repeater_express_explosive_feedback_ms", 300)},
        {"AMMO_REPEATER_HIGH_VELOCITY", get_or_default_feedback_ms("repeater_high_velocity_feedback_ms", 220)},
        {"AMMO_REPEATER_SPLIT_POINT", get_or_default_feedback_ms("repeater_split_point_feedback_ms", 220)},
        {"AMMO_REVOLVER", get_or_default_feedback_ms("revolver_feedback_ms", 110)},
        {"AMMO_REVOLVER_EXPRESS", get_or_default_feedback_ms("revolver_express_feedback_ms", 110)},
        {"AMMO_REVOLVER_EXPRESS_EXPLOSIVE", get_or_default_feedback_ms("revolver_express_explosive_feedback_ms", 220)},
        {"AMMO_REVOLVER_HIGH_VELOCITY", get_or_default_feedback_ms("revolver_high_velocity_feedback_ms", 110)},
        {"AMMO_REVOLVER_SPLIT_POINT", get_or_default_feedback_ms("revolver_split_point_feedback_ms", 110)},
        {"AMMO_RIFLE", get_or_default_feedback_ms("rifle_feedback_ms", 200)},
        {"AMMO_RIFLE_EXPRESS", get_or_default_feedback_ms("rifle_express_feedback_ms", 220)},
        {"AMMO_RIFLE_EXPRESS_EXPLOSIVE", get_or_default_feedback_ms("rifle_express_explosive_feedback_ms", 350)},
        {"AMMO_RIFLE_HIGH_VELOCITY", get_or_default_feedback_ms("rifle_high_velocity_feedback_ms", 220)},
        {"AMMO_RIFLE_SPLIT_POINT", get_or_default_feedback_ms("rifle_split_point_feedback_ms", 220)},
        {"AMMO_RIFLE_ELEPHANT", get_or_default_feedback_ms("rifle_elephant_feedback_ms", 500)},
        {"AMMO_SHOTGUN", get_or_default_feedback_ms("shotgun_feedback_ms", 400)},
        {"AMMO_SHOTGUN_SLUG", get_or_default_feedback_ms("shotgun_slug_feedback_ms", 400)},
        {"AMMO_SHOTGUN_SLUG_EXPLOSIVE", get_or_default_feedback_ms("shotgun_slug_explosive_feedback_ms", 500)},
        {"AMMO_SHOTGUN_BUCKSHOT_INCENDIARY", get_or_default_feedback_ms("shotgun_buckshot_incendiary_feedback_ms", 450)},
    };
    
    return feedbacks;
}
