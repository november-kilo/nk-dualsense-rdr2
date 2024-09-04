#pragma once

class game_effect
{
public:
    game_effect() = default;
    game_effect(const game_effect&) = delete;
    game_effect& operator=(const game_effect&) = delete;
    game_effect(game_effect&&) = delete;
    game_effect& operator=(game_effect&&) = delete;
    virtual ~game_effect() = default;

    virtual void on_tick() = 0;
};
