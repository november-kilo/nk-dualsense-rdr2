#include "shooting_feedback_effect.h"

void shooting_feedback_effect::on_tick() {
    if (player_util::is_shooting()) {
        shooting_feedback_start_time_ = time_util::time_now();
    }

    if (should_feedback()) {
        dual_sense_controller::set_right_trigger_rumble(true);
    }
}

bool shooting_feedback_effect::should_feedback() const {
    const std::chrono::milliseconds then = shooting_feedback_start_time_ + shooting_feedback::get_shooting_feedback_ms(player_util::get_weapon());

    return time_util::time_now() < then;
}
