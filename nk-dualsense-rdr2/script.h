#pragma once

#include <functional>
#include <memory>
#include <windows.h>

#include "console.h"
#include "dual_sense_controller.h"
#include "keyboard.h"
#include "mod_context.h"
#include "properties.h"
#include "shooting_feedback_effect.h"
#include "weapon_degradation_effect.h"
#include "../inc/ds5w.h"
#include "../inc/main.h"

enum : int { device_enum_info_dim = 16 };
using effect_generator = std::function<std::shared_ptr<game_effect>()>;

void on_script_register();
