#pragma once

#include <chrono>

#include "dual_sense_controller.h"
#include "game_effect.h"
#include "properties.h"
#include "shooting_feedback.h"
#include "util.h"

class shooting_feedback_effect final : public game_effect
{
public:
    shooting_feedback_effect();

    void on_tick() override;

private:
    std::chrono::milliseconds shooting_feedback_start_time_;
    unsigned char left_rumble_;
    unsigned char right_rumble_;

    
    [[nodiscard]] bool should_feedback() const;
};
