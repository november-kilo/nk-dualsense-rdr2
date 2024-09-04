#include "dual_sense_controller.h"

void dual_sense_controller::set_right_trigger_rumble(const bool rumbling) {
    DS5W::DeviceContext device_context = mod_context::get_instance().get_device_context();

    if (rumbling) {
        DS5W::DS5OutputState ds5_output_state;
        ZeroMemory(&ds5_output_state, sizeof(DS5W::DS5OutputState));
        ds5_output_state.leftRumble = 0;
        ds5_output_state.rightRumble = 255;
        DS5W::setDeviceOutputState(&device_context, &ds5_output_state);
    }
}

void dual_sense_controller::set_right_trigger_resistance(const int resistance) {
    DS5W::DS5OutputState ds5_output_state;
    ZeroMemory(&ds5_output_state, sizeof(DS5W::DS5OutputState));
    
    if (resistance == 0) {
        ds5_output_state.rightTriggerEffect.effectType = DS5W::TriggerEffectType::NoResitance;
    } else {
        const unsigned char uc_resistance = static_cast<unsigned char>(resistance);
        ds5_output_state.rightTriggerEffect.effectType = DS5W::TriggerEffectType::EffectEx;
        ds5_output_state.rightTriggerEffect.EffectEx.startPosition = 1;
        ds5_output_state.rightTriggerEffect.EffectEx.keepEffect = true;
        ds5_output_state.rightTriggerEffect.EffectEx.beginForce = uc_resistance;
        ds5_output_state.rightTriggerEffect.EffectEx.middleForce = uc_resistance;
        ds5_output_state.rightTriggerEffect.EffectEx.endForce = uc_resistance;
        ds5_output_state.rightTriggerEffect.EffectEx.frequency = 1;
    }

    DS5W::DeviceContext device_context = mod_context::get_instance().get_device_context();
    DS5W::setDeviceOutputState(&device_context, &ds5_output_state);
}

void dual_sense_controller::on_tick() const {
    for (const auto& effect : game_effects_) {
        effect->on_tick();
    }
}

void dual_sense_controller::add_game_effects(const std::vector<std::shared_ptr<game_effect>>& effects) {
    for (const auto& effect : effects) {
        add_game_effect(effect);
    }
}

void dual_sense_controller::add_game_effect(const std::shared_ptr<game_effect>& effect) {
    game_effects_.push_back(effect);
}
