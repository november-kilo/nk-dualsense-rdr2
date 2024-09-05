#include "weapon_degradation_effect.h"

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
