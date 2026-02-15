#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>

#include "Headers/Enemy.h"
#include "Headers/EnemyFactory.h"
#include "Headers/InventoryFactory.h"
#include "Headers/MainCharacter.h"
#include "Headers/UseableItems.h"
#include "Headers/Weapon.h"
#include "SaveSystem.h"

namespace
{
std::string TimestampNow()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&tt);
    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

std::string BuildSlotId()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&tt);
    std::ostringstream out;
    out << "save_" << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return out.str();
}

MainCharacter* MakePlayer(const std::string& name)
{
    MainCharacter* player = new MainCharacter(name, 100, 0, 100, "Unknown", 300);
    if (std::unique_ptr<Weapon> starterWeapon = CreateWeaponByName("Katana"))
    {
        player->addWeapon(starterWeapon.release());
    }
    if (std::unique_ptr<UseableItems> starterItem = CreateItemByName("Egg"))
    {
        player->addUseableItems(starterItem.release());
    }
    return player;
}

void ClearEnemy(GameSession& session)
{
    if (!session.enemy)
    {
        return;
    }

    delete session.enemy->getEnemyController();
    delete session.enemy->getEnemyView();
    delete session.enemy->getEnemyModel();
    delete session.enemy;
    session.enemy = nullptr;
}

GameState ToGameState(MainCharacter* player)
{
    GameState state;
    state.playerName = player->getName();
    state.gender = player->getGender();
    state.hp = player->getHP();
    state.xp = player->getXP();
    state.lvl = player->getLevel();
    state.coins = player->getGold();
    state.stamina = player->getStamina();
    state.kills = player->getKills();

    for (Weapon* weapon : player->getWeapons())
    {
        state.weaponsOwnedNames.push_back(weapon->getName());
    }
    for (UseableItems* item : player->getUseableItems())
    {
        state.usableItemsOwnedNames.push_back(item->getName());
    }
    if (!state.weaponsOwnedNames.empty())
    {
        state.equippedWeapon = state.weaponsOwnedNames.front();
        state.dm = player->getWeapons().front()->getDamagePerAttack();
    }

    return state;
}

MainCharacter* FromGameState(const GameState& state)
{
    MainCharacter* player = new MainCharacter(state.playerName, state.hp, state.xp, state.stamina, state.gender, state.coins);
    player->setLevel(state.lvl);
    player->setKills(state.kills);

    for (const std::string& weaponName : state.weaponsOwnedNames)
    {
        if (std::unique_ptr<Weapon> weapon = CreateWeaponByName(weaponName))
        {
            player->addWeapon(weapon.release());
        }
    }

    for (const std::string& itemName : state.usableItemsOwnedNames)
    {
        if (std::unique_ptr<UseableItems> item = CreateItemByName(itemName))
        {
            player->addUseableItems(item.release());
        }
    }

    if (!state.equippedWeapon.empty())
    {
        std::vector<Weapon*>& weapons = player->getWeapons();
        const auto it = std::find_if(weapons.begin(), weapons.end(), [&](Weapon* w) { return w->getName() == state.equippedWeapon; });
        if (it != weapons.end() && it != weapons.begin())
        {
            std::iter_swap(weapons.begin(), it);
        }
    }

    return player;
}

std::string PartyPreview(const std::vector<GameState>& party)
{
    std::string preview;
    for (size_t i = 0; i < party.size(); ++i)
    {
        if (i > 0)
        {
            preview += ", ";
        }
        preview += party[i].playerName;
    }
    return preview;
}

int AlivePlayers(const GameSession& session)
{
    int alive = 0;
    for (MainCharacter* player : session.party)
    {
        if (player->getHP() > 0)
        {
            ++alive;
        }
    }
    return alive;
}
} // namespace

GameSession CreateNewSessionSingle(const std::string& playerName)
{
    GameSession session;
    session.multiplayer = false;
    session.party.push_back(MakePlayer(playerName.empty() ? "Player1" : playerName));
    session.combatLog.push_back("New single-player session started.");
    return session;
}

GameSession CreateNewSessionMulti(const std::vector<std::string>& playerNames)
{
    GameSession session;
    session.multiplayer = true;

    for (size_t i = 0; i < playerNames.size(); ++i)
    {
        const std::string fallback = "Player" + std::to_string(i + 1);
        session.party.push_back(MakePlayer(playerNames[i].empty() ? fallback : playerNames[i]));
    }

    if (session.party.empty())
    {
        session.party.push_back(MakePlayer("Player1"));
    }

    session.combatLog.push_back("New multiplayer session started.");
    return session;
}

bool SaveSession(const GameSession& session, const std::string& slotId, std::string& err, const std::string& slotLabel)
{
    SessionState save;
    save.slotId = slotId.empty() ? BuildSlotId() : slotId;
    save.slotLabel = slotLabel.empty() ? save.slotId : slotLabel;
    save.createdAt = TimestampNow();
    save.updatedAt = TimestampNow();
    save.mode = session.multiplayer ? "multiplayer" : "singleplayer";
    save.partySize = static_cast<int>(session.party.size());
    save.difficulty = session.difficulty;
    save.battleIndex = session.battleIndex;

    for (MainCharacter* player : session.party)
    {
        save.party.push_back(ToGameState(player));
    }

    if (!::SaveSession(save, save.slotId, &err))
    {
        return false;
    }

    return true;
}

bool LoadSession(GameSession& session, const std::string& slotId, std::string& err)
{
    SessionState loaded;
    if (!::LoadSession(loaded, slotId, &err))
    {
        return false;
    }

    DestroySession(session);
    session.multiplayer = (loaded.mode == "multiplayer");
    session.difficulty = loaded.difficulty;
    session.battleIndex = loaded.battleIndex;
    session.activeSlotId = loaded.slotId;
    session.activeSlotLabel = loaded.slotLabel;

    for (const GameState& playerState : loaded.party)
    {
        session.party.push_back(FromGameState(playerState));
    }

    session.combatLog.push_back("Session loaded from slot: " + slotId);
    return true;
}

std::vector<SlotInfo> ListSessionSlots()
{
    std::vector<SlotInfo> out;
    namespace fs = std::filesystem;
    std::error_code ec;
    if (!fs::exists("saves", ec))
    {
        return out;
    }

    for (const fs::directory_entry& entry : fs::directory_iterator("saves", ec))
    {
        if (ec || !entry.is_regular_file() || entry.path().extension() != ".json")
        {
            continue;
        }

        SessionSlotPreview preview;
        std::string err;
        const std::string slotId = entry.path().stem().string();
        SlotInfo row;
        row.slotId = slotId;

        if (!LoadSessionPreview(preview, slotId, &err))
        {
            row.slotLabel = slotId;
            row.updatedAt = "invalid";
            row.partyPreview = err;
            row.isCorrupt = true;
            out.push_back(row);
            continue;
        }

        row.slotLabel = preview.slotLabel.empty() ? slotId : preview.slotLabel;
        row.updatedAt = preview.updatedAt;
        for (size_t i = 0; i < preview.partyPreview.size(); ++i)
        {
            if (i > 0)
            {
                row.partyPreview += ", ";
            }
            row.partyPreview += preview.partyPreview[i];
        }
        row.isCorrupt = preview.isCorrupt;
        out.push_back(row);
    }

    std::sort(out.begin(), out.end(), [](const SlotInfo& a, const SlotInfo& b) { return a.updatedAt > b.updatedAt; });
    return out;
}

void StartBattle(GameSession& session)
{
    if (session.party.empty())
    {
        return;
    }

    ClearEnemy(session);

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> typeDist(0, 1);

    EnemyFactory factory(session.party.front(), std::max(1, session.difficulty));
    session.enemy = (typeDist(rng) == 0) ? static_cast<Enemy*>(factory.makeZombie()) : static_cast<Enemy*>(factory.makeHuman());

    session.inBattle = true;
    session.battleIndex++;
    session.combatLog.push_back("Battle started against " + session.enemy->getEnemyModel()->getName() + ".");
}

BattleStepResult PlayerAction(GameSession& session, int playerIndex, ActionType actionType, int selectedIndex)
{
    BattleStepResult result;
    if (!session.inBattle || !session.enemy || playerIndex < 0 || playerIndex >= static_cast<int>(session.party.size()))
    {
        result.message = "Invalid action context.";
        return result;
    }

    MainCharacter* player = session.party[playerIndex];
    if (player->getHP() <= 0)
    {
        result.message = player->getName() + " is down.";
        return result;
    }

    if (actionType == ActionType::Run)
    {
        session.inBattle = false;
        result.success = true;
        result.battleEnded = true;
        result.message = player->getName() + " fled the battle.";
        session.combatLog.push_back(result.message);
        return result;
    }

    if (actionType == ActionType::SwitchWeapon)
    {
        std::vector<Weapon*>& weapons = player->getWeapons();
        if (selectedIndex < 0 || selectedIndex >= static_cast<int>(weapons.size()))
        {
            result.message = "Invalid weapon selection.";
            return result;
        }

        std::iter_swap(weapons.begin(), weapons.begin() + selectedIndex);
        result.success = true;
        result.message = player->getName() + " equipped " + weapons.front()->getName() + ".";
        session.combatLog.push_back(result.message);
        return result;
    }

    if (actionType == ActionType::UseItem)
    {
        if (selectedIndex < 0 || selectedIndex >= static_cast<int>(player->getUseableItems().size()))
        {
            result.message = "Invalid item selection.";
            return result;
        }
        const std::string itemName = player->getUseableItems()[selectedIndex]->getName();
        player->useItem(selectedIndex + 1);
        result.success = true;
        result.message = player->getName() + " used " + itemName + ".";
        session.combatLog.push_back(result.message);
        return result;
    }

    if (actionType == ActionType::Attack)
    {
        if (player->getWeapons().empty())
        {
            result.message = "No weapon equipped.";
            return result;
        }

        const int enemyHpBefore = session.enemy->getEnemyModel()->getHP();
        Weapon* weapon = player->getWeapons().front();
        player->Attack(session.enemy, weapon);
        const int enemyHpAfter = session.enemy->getEnemyModel()->getHP();

        result.success = true;
        result.message = player->getName() + " attacks with " + weapon->getName() + ": "
            + std::to_string(std::max(0, enemyHpBefore - enemyHpAfter)) + " dmg. Enemy HP "
            + std::to_string(enemyHpBefore) + " -> " + std::to_string(std::max(0, enemyHpAfter));
        session.combatLog.push_back(result.message);

        if (enemyHpAfter <= 0)
        {
            session.inBattle = false;
            result.battleEnded = true;
            session.combatLog.push_back("Enemy defeated.");
            for (MainCharacter* p : session.party)
            {
                p->setGold(p->getGold() + 40);
                p->setXP(p->getXP() + 30);
                p->CalculateLevel();
            }
        }

        return result;
    }

    result.message = "Unsupported action.";
    return result;
}

EnemyTurnResult EnemyTurn(GameSession& session)
{
    EnemyTurnResult out;
    if (!session.inBattle || !session.enemy)
    {
        return out;
    }

    for (MainCharacter* player : session.party)
    {
        if (player->getHP() <= 0)
        {
            continue;
        }

        const int hpBefore = player->getHP();
        session.enemy->getEnemyController()->Attack(player);
        const int hpAfter = player->getHP();

        std::string line = session.enemy->getEnemyModel()->getName() + " attacks " + player->getName()
            + ": " + std::to_string(std::max(0, hpBefore - hpAfter)) + " dmg. HP "
            + std::to_string(hpBefore) + " -> " + std::to_string(std::max(0, hpAfter));

        out.lines.push_back(line);
        session.combatLog.push_back(line);
        out.anyAction = true;
    }

    if (AlivePlayers(session) == 0)
    {
        session.inBattle = false;
        out.battleEnded = true;
        session.combatLog.push_back("All players are down.");
    }

    return out;
}

std::vector<PlayerSnapshot> GetPartySnapshot(const GameSession& session)
{
    std::vector<PlayerSnapshot> out;
    for (MainCharacter* player : session.party)
    {
        PlayerSnapshot row;
        row.name = player->getName();
        row.hp = player->getHP();
        row.maxHp = 90 + player->getLevel() * 10;
        row.stamina = player->getStamina();
        row.coins = player->getGold();
        row.level = player->getLevel();

        for (Weapon* weapon : player->getWeapons())
        {
            row.weapons.push_back(weapon->getName());
        }
        for (UseableItems* item : player->getUseableItems())
        {
            row.items.push_back(item->getName());
        }
        out.push_back(row);
    }
    return out;
}

EnemySnapshot GetEnemySnapshot(const GameSession& session)
{
    EnemySnapshot out;
    if (!session.enemy)
    {
        return out;
    }

    out.name = session.enemy->getEnemyModel()->getName();
    out.hp = session.enemy->getEnemyModel()->getHP();
    out.maxHp = std::max(out.hp, 1);
    return out;
}

bool BuyWeapon(GameSession& session, int playerIndex, const std::string& weaponName, std::string& err)
{
    if (playerIndex < 0 || playerIndex >= static_cast<int>(session.party.size()))
    {
        err = "Invalid player index.";
        return false;
    }

    MainCharacter* player = session.party[playerIndex];
    std::unique_ptr<Weapon> weapon = CreateWeaponByName(weaponName);
    if (!weapon)
    {
        err = "Unknown weapon.";
        return false;
    }

    if (player->getGold() < weapon->getPrice())
    {
        err = "Not enough gold.";
        return false;
    }

    player->setGold(player->getGold() - weapon->getPrice());
    player->addWeapon(weapon.release());
    session.combatLog.push_back(player->getName() + " bought " + weaponName + ".");
    return true;
}

bool BuyItem(GameSession& session, int playerIndex, const std::string& itemName, std::string& err)
{
    if (playerIndex < 0 || playerIndex >= static_cast<int>(session.party.size()))
    {
        err = "Invalid player index.";
        return false;
    }

    MainCharacter* player = session.party[playerIndex];
    std::unique_ptr<UseableItems> item = CreateItemByName(itemName);
    if (!item)
    {
        err = "Unknown item.";
        return false;
    }

    if (player->getGold() < item->getPrice())
    {
        err = "Not enough gold.";
        return false;
    }

    player->setGold(player->getGold() - item->getPrice());
    player->addUseableItems(item.release());
    session.combatLog.push_back(player->getName() + " bought " + itemName + ".");
    return true;
}

void DestroySession(GameSession& session)
{
    ClearEnemy(session);
    for (MainCharacter* player : session.party)
    {
        delete player;
    }
    session.party.clear();
    session.inBattle = false;
}
