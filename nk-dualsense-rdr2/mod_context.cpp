#include "mod_context.h"

void mod_context::zero_output_state() {
    DS5W::DS5OutputState ds5_output_state;
    ZeroMemory(&ds5_output_state, sizeof(DS5W::DS5OutputState));
    ds5_output_state.rightTriggerEffect.effectType = DS5W::TriggerEffectType::NoResitance;
    DS5W::setDeviceOutputState(&device_context_, &ds5_output_state);
}

void mod_context::on_detach() {
    get_instance().zero_output_state();
    DS5W::freeDeviceContext(&device_context_);
}

void mod_context::set_device_context(const DS5W::DeviceContext& new_device_context) {
    device_context_ = new_device_context;
}

const DS5W::DeviceContext& mod_context::get_device_context() const {
    return device_context_;
}
