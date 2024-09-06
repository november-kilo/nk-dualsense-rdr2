# nk-2dualsense-rdr2 mod

This is a Red Dead Redemption 2 single-player mod
implemented with Alexander Blade's [ScriptHookRDR2](http://dev-c.com/rdr2/scripthookrdr2/)
and uses [DualSense-Windows](https://github.com/Ohjurot/DualSense-Windows)
to implement:
* Trigger resistance proportional to current weapon condition
* Rumble when shooting

## Installation

Place the three files  in `bin\Release` in Red Dead Redemption 2's game folder:
* ds5w_x64.dll
* nk-dualsense-rdr2.asi
* nk-dualsense-rdr2.properties

`ds5w_x64.dll` is from the DualSense-Windows release.

`nk-dualsense-rdr2.asi` is the compiled mod.

`nk-dualsense-rdr2.properties` provides configurable values used by the mod.

Remove these files before playing Red Dead Online.

## Development

The header file, `ds5w.h`, from the DualSense-Windows release build
goes into the ScriptHookRDR2 `inc/` directory.

The lib file, `ds5w_x64.lib`, from the DualSense-Windows release
build goes into the ScriptHookRDR2 `lib/` directory.

One way to implement a new effect to the mod is to
create a new effect by inheriting `game_effect`
(`game_effect.h`) and overriding the `on_tick()` function.
Then add the effect in the function `initialize_controller()`
in `script.cpp`.
The `on_tick()` function will get called every game tick.
