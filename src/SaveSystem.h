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

struct SessionState
{
    int version = 3;
    std::string slotId;
    std::string slotLabel;
    std::string createdAt;
    std::string updatedAt;
    std::string mode = "singleplayer";
    int partySize = 0;
    std::vector<GameState> party;
    bool sharedCoins = false;
    int difficulty = 1;
    int battleIndex = 0;
};

struct SessionSlotPreview
{
    std::string slotId;
    std::string slotLabel;
    std::string createdAt;
    std::string updatedAt;
    std::string mode;
    std::vector<std::string> partyPreview;
    bool isCurrentSlot = false;
    bool isLegacy = false;
    bool isCorrupt = false;
};

bool SaveGame(const GameState& state, const std::string& slotName, std::string* err);
bool LoadGame(GameState& outState, const std::string& slotName, std::string* err);
bool SaveSession(const SessionState& state, const std::string& slotName, std::string* err);
bool LoadSession(SessionState& outState, const std::string& slotName, std::string* err);
bool LoadSessionPreview(SessionSlotPreview& outPreview, const std::string& slotName, std::string* err);
