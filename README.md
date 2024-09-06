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

`nk-dualsense-rdr2.properties` defines properties used by the mod.

Remove these files before playing Red Dead Online.

## Development

### Setup

The header file, `ds5w.h`, from the DualSense-Windows release build
goes into the ScriptHookRDR2 `inc/` directory.

The lib file, `ds5w_x64.lib`, from the DualSense-Windows release
build goes into the ScriptHookRDR2 `lib/` directory.

### New effects
One way to implement a new effect is to inherit `game_effect`
(`game_effect.h`) and override the `on_tick()` function.
Then add the effect to `effects_map`
in `script.cpp`. Finally, update the properties file to enable
the effect.
The `on_tick()` function will get called every game tick.
