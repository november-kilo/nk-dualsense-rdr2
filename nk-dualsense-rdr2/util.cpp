#include "util.h"

#include "console.h"

Hash util::get_hash(const std::string& key) {
    return GAMEPLAY::GET_HASH_KEY(const_cast<char*>(key.c_str()));
}

std::chrono::milliseconds time_util::time_now() {
    const auto now = std::chrono::system_clock::now();
    const auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    const auto epoch = now_ms.time_since_epoch();
    const auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    return value;
}

Hash player_util::get_ammo_type() {
    const Entity weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0);
    return WEAPON::_0x7E7B19A4355FEE13(PLAYER::PLAYER_PED_ID(), weapon_entity);
}

Hash player_util::get_weapon() {
    const Ped player_ped = PLAYER::PLAYER_PED_ID();
    Hash weapon;

    if (!WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(player_ped, &weapon)) {
        if (!WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weapon, 0, 0, 0)) {
            return 0;
        }
    }
    
    return weapon;
}

float player_util::get_weapon_degradation() {
    const Entity weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0);
    return WEAPON::_0x0D78E1097F89E637(weapon_entity);
}

bool player_util::is_shooting() {
    return PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID());
}

bool player_util::is_weapon_gun() {
    return WEAPON::_0x705BE297EEBDB95D(get_weapon());
}

bool player_util::is_weapon_cannon() {
    static constexpr Hash gatling_gun = 3666182381;
    static constexpr Hash maxim_gun = 3101324918;
    static constexpr Hash hotchkiss_cannon = 2465730487;
    const Hash player_weapon = get_weapon();
    
    return player_weapon == gatling_gun || player_weapon == maxim_gun || player_weapon == hotchkiss_cannon;
}

bool player_util::is_gun_silent() {
    const bool is_gun = is_weapon_gun();
    const bool is_silent = WEAPON::_0x5809DBCA0A37C82B(get_weapon());
    return !is_gun && is_silent;
}
