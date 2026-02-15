#pragma once

#include <string>
#include <vector>

class MainCharacter;
class Enemy;

struct SlotInfo
{
    std::string slotId;
    std::string slotLabel;
    std::string updatedAt;
    std::string partyPreview;
    bool isCorrupt = false;
};

struct PlayerSnapshot
{
    std::string name;
    int hp = 0;
    int maxHp = 100;
    int stamina = 0;
    int coins = 0;
    int level = 1;
    std::vector<std::string> weapons;
    std::vector<std::string> items;
};

struct EnemySnapshot
{
    std::string name;
    int hp = 0;
    int maxHp = 100;
};

enum class ActionType
{
    Attack,
    UseItem,
    SwitchWeapon,
    Run
};

struct BattleStepResult
{
    bool success = false;
    bool battleEnded = false;
    std::string message;
};

struct EnemyTurnResult
{
    bool anyAction = false;
    bool battleEnded = false;
    std::vector<std::string> lines;
};

struct GameSession
{
    bool multiplayer = false;
    int difficulty = 1;
    int battleIndex = 0;
    bool inBattle = false;
    std::vector<MainCharacter*> party;
    Enemy* enemy = nullptr;
    std::vector<std::string> combatLog;
    std::string activeSlotId;
    std::string activeSlotLabel;
};

GameSession CreateNewSessionSingle(const std::string& playerName);
GameSession CreateNewSessionMulti(const std::vector<std::string>& playerNames);

bool LoadSession(GameSession& session, const std::string& slotId, std::string& err);
bool SaveSession(const GameSession& session, const std::string& slotId, std::string& err, const std::string& slotLabel = "");

std::vector<SlotInfo> ListSessionSlots();

void StartBattle(GameSession& session);
BattleStepResult PlayerAction(GameSession& session, int playerIndex, ActionType actionType, int selectedIndex);
EnemyTurnResult EnemyTurn(GameSession& session);

std::vector<PlayerSnapshot> GetPartySnapshot(const GameSession& session);
EnemySnapshot GetEnemySnapshot(const GameSession& session);

std::vector<std::string> GetAvailableWeapons();
std::vector<std::string> GetAvailableItems();

bool BuyWeapon(GameSession& session, int playerIndex, const std::string& weaponName, std::string& err);
bool BuyItem(GameSession& session, int playerIndex, const std::string& itemName, std::string& err);

void DestroySession(GameSession& session);
