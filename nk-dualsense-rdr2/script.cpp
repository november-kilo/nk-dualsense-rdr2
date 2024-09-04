#include "script.h"

#include "keyboard.h"
#include "shooting_feedback.h"

enum : int { device_enum_info_dim = 16 };

std::unique_ptr<dual_sense_controller> initialize_controller() {
    auto ds_controller = std::make_unique<dual_sense_controller>();
    ds_controller->add_game_effects({
        std::make_shared<weapon_degradation_effect>(),
        std::make_shared<shooting_feedback_effect>()
    });
    
    return ds_controller;
}

[[noreturn]]
void start_script_loop(const std::unique_ptr<dual_sense_controller>& controller) {
    srand(GetTickCount());
    
    while (true) {
        if (IsKeyJustUp(0x4e)) {
            mod_context::get_instance().zero();
        }
        
        controller->on_tick();
        WAIT(0);
    }
}

void on_script_register() {
    console::create_console();
    
    DS5W::DeviceEnumInfo device_enum_info[device_enum_info_dim];
    unsigned int controller_count = 0;
    if (DS5W::enumDevices(device_enum_info, device_enum_info_dim, &controller_count) == DS5W_OK) {
        DS5W::DeviceContext device_context;
		
        if (DS5W_SUCCESS(DS5W::initDeviceContext(&device_enum_info[0], &device_context))) {
            mod_context::get_instance().set_device_context(device_context);
            const auto controller = initialize_controller();
            shooting_feedback::init();
            start_script_loop(controller);
        }
    }
}
