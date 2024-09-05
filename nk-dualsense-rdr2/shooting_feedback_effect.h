#pragma once

#include <chrono>

#include "dual_sense_controller.h"
#include "game_effect.h"
#include "shooting_feedback.h"
#include "util.h"

class shooting_feedback_effect final : public game_effect
{
public:
    explicit shooting_feedback_effect() : shooting_feedback_start_time_(0) {}

    void on_tick() override;

private:
    std::chrono::milliseconds shooting_feedback_start_time_;

    [[nodiscard]] bool should_feedback() const;
};
