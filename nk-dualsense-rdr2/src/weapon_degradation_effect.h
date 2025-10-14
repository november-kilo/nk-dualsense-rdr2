#pragma once

#include "dual_sense_controller.h"
#include "game_effect.h"
#include "properties.h"
#include "util.h"

struct rgb_color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class weapon_degradation_effect final : public game_effect
{
public:
    weapon_degradation_effect();
    
    void on_tick() override;

private:
    int scheme_;
    
    static int convert_weapon_degradation_to_int(float weapon_degradation);
    static int calculate_trigger_resistance();
    [[nodiscard]] rgb_color calculate_degradation_color(int degradation) const;
};
