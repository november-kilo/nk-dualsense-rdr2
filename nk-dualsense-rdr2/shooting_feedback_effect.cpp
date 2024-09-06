#include "shooting_feedback_effect.h"

shooting_feedback_effect::shooting_feedback_effect() {
    shooting_feedback_start_time_ = std::chrono::milliseconds{0};
    left_rumble_ = shooting_feedback::get_left_rumble();
    right_rumble_ = shooting_feedback::get_right_rumble();
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
    const std::chrono::milliseconds then = shooting_feedback_start_time_ + shooting_feedback::get_milliseconds_to_wait(player_util::get_weapon());

    return time_util::time_now() < then;
}
