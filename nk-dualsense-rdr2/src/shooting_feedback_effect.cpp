#include "shooting_feedback_effect.h"

shooting_feedback_effect::shooting_feedback_effect() {
    shooting_feedback_start_time_ = std::chrono::milliseconds{0};
    left_rumble_ = get_rumble("shooting_feedback_left_rumble", 0);
    right_rumble_ = get_rumble("shooting_feedback_right_rumble", 255);
}

void shooting_feedback_effect::on_tick() {
    if (player_util::is_shooting()) {
        shooting_feedback_start_time_ = time_util::time_now();
    }

    if (should_feedback()) {      
        dual_sense_controller::set_rumble(left_rumble_, right_rumble_);
    }
}

bool shooting_feedback_effect::should_feedback() const {
    long shooting_feedback_wait_time_ms = properties::get_instance().get_or_default("shooting_feedback_wait_time_ms", static_cast<long>(100));
    if (player_util::is_weapon_cannon()) {
        shooting_feedback_wait_time_ms *= properties::get_instance().get_or_default("shooting_cannon_feedback_wait_time_multiplier", static_cast<long>(5));
    }
    
    const std::chrono::milliseconds then = shooting_feedback_start_time_ + std::chrono::milliseconds{shooting_feedback_wait_time_ms};

    return time_util::time_now() < then;
}

unsigned char shooting_feedback_effect::get_rumble(const std::string& key, const long default_value) {
    const long configured_rumble = properties::get_instance().get_or_default(key, default_value);
    return util::to_unsigned_char(configured_rumble);
}
