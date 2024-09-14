#pragma once

#include "dual_sense_controller.h"
#include "game_effect.h"
#include "util.h"

class weapon_degradation_effect final : public game_effect
{
public:
    void on_tick() override;

private:
    static int convert_weapon_degradation_to_resistance(float weapon_degradation);
    static int calculate_trigger_resistance();
};
