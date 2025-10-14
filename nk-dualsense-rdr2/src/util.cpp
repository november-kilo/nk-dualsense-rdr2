#include "util.h"

#include "console.h"

Hash util::get_hash(const std::string& key) {
    return GAMEPLAY::GET_HASH_KEY(const_cast<char*>(key.c_str()));
}

char* util::create_string(const std::string& text) {
    return GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(text.c_str()));
}

std::chrono::milliseconds time_util::time_now() {
    const auto now = std::chrono::system_clock::now();
    const auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    const auto epoch = now_ms.time_since_epoch();
    const auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    return value;
}

Hash player_util::get_ammo_type() {
    const Ped player_ped = PLAYER::PLAYER_PED_ID();
    const Entity weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(player_ped, 0);
    
    return WEAPON::_0x7E7B19A4355FEE13(player_ped, weapon_entity);
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

void ui_util::subtitle(const std::string& text) {
    char* c_text = util::create_string(text);
    UILOG::_0xFA233F8FE190514C(reinterpret_cast<Any*>(c_text));
    UILOG::_0xE9990552DEC71600();
    UILOG::_0xA3108D6981A5CADB();
    UILOG::_0xDFF0D417277B41F8();
}

void ui_util::debug(const std::string& text) {
    char* c_text = util::create_string(text);
    UI::DRAW_TEXT(c_text, 0, 0);
}

unsigned char weapon_util::degradation_r(const int value, const int scheme) {
    return util::to_unsigned_char(value);    
}

unsigned char weapon_util::degradation_g(const int value, const int scheme) {
    if (scheme == 0) {
        return util::to_unsigned_char(255 - value);    
    }
    return 0;
}

unsigned char weapon_util::degradation_b(const int value, const int scheme) {
    if (scheme == 0) {
        return 0;
    }

    return util::to_unsigned_char(255 - value);
}


