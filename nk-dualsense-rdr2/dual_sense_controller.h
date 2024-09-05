#pragma once

#include <memory>
#include <vector>
#include <windows.h>

#include "game_effect.h"
#include "mod_context.h"

class dual_sense_controller
{
public:
    static void set_right_trigger_rumble(bool rumbling);
    static void set_right_trigger_resistance(int resistance);
    
    void on_tick() const;
    void add_game_effects(const std::vector<std::shared_ptr<game_effect>>& effects);
    void add_game_effect(const std::shared_ptr<game_effect>& effect);

private:
    std::vector<std::shared_ptr<game_effect>> game_effects_;
};
