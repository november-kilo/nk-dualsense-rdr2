#pragma once

#include <chrono>
#include <cmath>

#include "dual_sense_controller.h"
#include "game_effect.h"
#include "util.h"

class weapon_degradation_effect final : public game_effect
{
public:
    void on_tick() override;

private:
    static int convert_weapon_degradation_to_resistance(float weapon_degradation);
};

class shooting_feedback_effect final : public game_effect
{
public:
    explicit shooting_feedback_effect() : shooting_feedback_start_time_(0) {}

    void on_tick() override;

private:
    std::chrono::milliseconds shooting_feedback_start_time_;
};