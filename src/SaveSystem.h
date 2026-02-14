#pragma once

#include <string>
#include <vector>

struct GameState
{
    std::string playerName;
    std::string gender;
    int hp = 0;
    int xp = 0;
    int dm = 0;
    int lvl = 1;
    int coins = 0;
    int stamina = 0;
    int kills = 0;
    std::string equippedWeapon;
    std::vector<std::string> weaponsOwnedNames;
    std::vector<std::string> usableItemsOwnedNames;
};

bool SaveGame(const GameState& state, const std::string& slotName, std::string* err);
bool LoadGame(GameState& outState, const std::string& slotName, std::string* err);
