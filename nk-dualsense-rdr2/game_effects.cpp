#include "game_effects.h"

#include "console.h"
#include "shooting_feedback.h"

int weapon_degradation_effect::convert_weapon_degradation_to_resistance(const float weapon_degradation) {
    return static_cast<int>(std::round(weapon_degradation * 255));
}

void weapon_degradation_effect::on_tick() {
    int resistance = 0;
    
    if (player_util::is_weapon_gun()) {
        const float weapon_degradation = player_util::get_weapon_degradation();
        resistance = convert_weapon_degradation_to_resistance(weapon_degradation);
    }
    
    dual_sense_controller::set_right_trigger_resistance(resistance);
}

void shooting_feedback_effect::on_tick() {
    if (player_util::is_shooting()) {
        shooting_feedback_start_time_ = time_util::time_now();
    }

    if (time_util::time_now() < shooting_feedback_start_time_ + shooting_feedback::get_shooting_feedback_ms(player_util::get_weapon())) {
        dual_sense_controller::set_right_trigger_rumble(true);
    }
}
