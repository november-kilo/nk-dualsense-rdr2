#include "script.h"

std::unordered_map<std::string, effect_generator> effects_map = {
    {"shooting_feedback_effect", []{ return std::make_shared<shooting_feedback_effect>(); }},
    {"weapon_degradation_effect", []{ return std::make_shared<weapon_degradation_effect>(); }},
};

void add_effects_to_controller(const std::unique_ptr<dual_sense_controller>& ds_controller) {
    for (const auto& [effect_fn_key, effect_fn] : effects_map) {
        if (properties::get_instance().get_or_default(effect_fn_key, false)) {
            ds_controller->add_game_effect(effect_fn());
            console::write("added " + effect_fn_key);
        }
    }
}

void handle_keyboard_events() {
    if (IsKeyJustUp(0x4e)) { // N on keyboard
        mod_context::get_instance().zero_output_state();
    }
}

[[noreturn]]
void start_script_loop() {
    const auto ds_controller = std::make_unique<dual_sense_controller>();
    add_effects_to_controller(ds_controller);
    console::write("starting script loop");
    srand(GetTickCount());
    while (true) {
        handle_keyboard_events();
        ds_controller->on_tick();
        WAIT(0);
    }
}

void on_script_register() {
    console::create_console(properties::get_instance().get_or_default("open_console", false));
    DS5W::DeviceEnumInfo device_enum_info[device_enum_info_dim];
    unsigned int controller_count = 0;
    if (DS5W::enumDevices(device_enum_info, device_enum_info_dim, &controller_count) == DS5W_OK) {
        if (controller_count > 0) {
            DS5W::DeviceContext device_context;

            if (DS5W_SUCCESS(DS5W::initDeviceContext(&device_enum_info[0], &device_context))) {
                mod_context::get_instance().set_device_context(device_context);
                start_script_loop();
            }
        }
    }
}
