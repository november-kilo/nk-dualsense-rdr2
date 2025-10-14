#include "weapon_degradation_effect.h"

weapon_degradation_effect::weapon_degradation_effect() {
    scheme_ = properties::get_instance().get_or_default("weapon_degradation_led_scheme", 0);
}

int weapon_degradation_effect::convert_weapon_degradation_to_int(const float weapon_degradation) {
    return static_cast<int>(std::round(weapon_degradation * 255));
}

int weapon_degradation_effect::calculate_trigger_resistance() {
    if (player_util::is_weapon_gun()) {
        const float weapon_degradation = player_util::get_weapon_degradation();
        return convert_weapon_degradation_to_int(weapon_degradation);
    }
    return 0;
}

rgb_color weapon_degradation_effect::calculate_degradation_color(const int degradation) const {
    return {
        weapon_util::degradation_r(degradation, scheme_),
        weapon_util::degradation_g(degradation, scheme_),
        weapon_util::degradation_b(degradation, scheme_)
    };
}

void weapon_degradation_effect::on_tick() {
    const int degradation = calculate_trigger_resistance();
    const auto [r, g, b] = calculate_degradation_color(degradation);
    
    dual_sense_controller::set_right_trigger_resistance(degradation);
    dual_sense_controller::set_lightbar(r, g, b);
}
