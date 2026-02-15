#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include<sstream>
#include<cmath>
#include<ctime>
#include<fstream>
#include<filesystem>
#include<limits>
#include<memory>
#include<stdlib.h>
#include <thread>
#include <random>
#include <algorithm>
#include <cassert>
#include <random>
#include "SaveSystem.h"
#include "Headers/ConsoleUI.h"
#include "Headers/Items.h"
#include "Headers/Items.h"
#include "Headers/EnemyFactory.h"
#include "Headers/EnemyFactory.h"
#include "Headers/Zombie.h"
#include "Headers/Zombie.h"
#include "Headers/Enemy.h"
#include "Headers/Enemy.h"
#include "Headers/MainCharacter.h"
#include "Headers/MainCharacter.h"
#include "Headers/Shop.h"
#include "Headers/Shop.h"
#include "Headers/UseableItems.h"
#include "Headers/UseableItems.h"
#include "Headers/PermenantWeapon.h"
#include "Headers/PermenantWeapon.h"
#include "Headers/ThrowableWeapon.h"
#include "Headers/ThrowableWeapon.h"
#include "Headers/Weapon.h"
#include "Headers/Weapon.h"
#include "Headers/ColdWeapon.h"
#include "Headers/ColdWeapon.h"
#include "Headers/HotWeapon.h"
#include "Headers/HotWeapon.h"
#include "Headers/Batarang.h"
#include "Headers/Batarang.h"
#include "Headers/Katana.h"
#include "Headers/Katana.h"
#include "Headers/grenade.h"
#include "Headers/grenade.h"
#include "Headers/Egg.h"
#include "Headers/Egg.h"
#include "Headers/WheyProtein.h"
#include "Headers/WheyProtein.h"
#include "Headers/Blaster.h"
#include "Headers/Blaster.h"
#include "Headers/human.h"
#include "Headers/human.h"
#include "Headers/KratosBlades.h"
#include "Headers/KratosBlades.h"
#include "Headers/EnergyDrink.h"
#include "Headers/EnergyDrink.h"
#include "Headers/shuriken.h"
#include "Headers/shuriken.h"
#include "Headers/Spear.h"
#include "Headers/Spear.h"
#include "Headers/XPpotion.h"
#include "Headers/XPpotion.h"
#include "Headers/Mjolnir.h"
#include "Headers/Mjolnir.h"
#include "Headers/MiniGun.h"
#include "Headers/MiniGun.h"
#include "Headers/RocketLauncher.h"
#include "Headers/RocketLauncher.h"
#include "Headers/InventoryFactory.h"

using namespace std;
ifstream userList ("data/users.txt");

#ifdef DEBUG_LOG
#define DBG_LOG(msg) do { std::clog << "[DEBUG] " << msg << std::endl; } while(false)
#else
#define DBG_LOG(msg) do {} while(false)
#endif

const int NORMAL_PAUSE_MS = 1200;

void uiBattleStatus(MainCharacter* warrior, Enemy* enemy)
{
    string lineOne =
        "Warrior HP: " + to_string(warrior->getHP()) +
        " | Warrior ST: " + to_string(warrior->getStamina()) +
        " | Enemy HP: " + to_string(enemy->getEnemyModel()->getHP());

    string enemyDamage = enemy->getEnemyModel()->getName() == "Human"
                             ? "Enemy DMPA: Weapon based"
                             : "Enemy DMPA: " + to_string(enemy->getEnemyModel()->getDamagePerAttack());

    string lineTwo = enemyDamage + " | Enemy ST: " + to_string(enemy->getEnemyModel()->getStamina());

    ui::centeredLine(lineOne);
    ui::centeredLine(lineTwo);
    ui::drawDivider('-', 64);
}

void pauseForReadability(int ms = NORMAL_PAUSE_MS)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}
void printS(const string& s)
{
    cout << s << endl << endl;
}

void waitForEnterToContinue()
{
    if (cin.fail())
    {
        cin.clear();
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void prints(const string& s)
{
    cout << s << endl << endl;
}

//Global Objects And Variables==============================
    // static MainCharacter Warior;
    Shop* Store;
    int ZZAARRIIBB;

    int numberOfCharacters;
    static vector<MainCharacter*>Wariors;
    int gCurrentDifficulty = 1;
    int gCurrentBattleIndex = 0;

GameState BuildGameStateFromWarrior(MainCharacter* warrior)
{
    GameState state;
    state.playerName = warrior->getName();
    state.gender = warrior->getGender();
    state.hp = warrior->getHP();
    state.xp = warrior->getXP();
    state.lvl = warrior->getLevel();
    state.coins = warrior->getGold();
    state.stamina = warrior->getStamina();
    state.kills = warrior->getKills();

    const vector<Weapon*>& weapons = warrior->getWeapons();
    for (Weapon* weapon : weapons)
    {
        state.weaponsOwnedNames.push_back(weapon->getName());
    }
    if (!state.weaponsOwnedNames.empty())
    {
        state.equippedWeapon = state.weaponsOwnedNames.front();
        state.dm = weapons.front()->getDamagePerAttack();
    }

    const vector<UseableItems*>& items = warrior->getUseableItems();
    for (UseableItems* item : items)
    {
        state.usableItemsOwnedNames.push_back(item->getName());
    }

    return state;
}

bool ReorderEquippedWeapon(MainCharacter* warrior, const string& equippedWeaponName)
{
    if (equippedWeaponName.empty())
    {
        return true;
    }

    vector<Weapon*>& weapons = warrior->getWeapons();
    auto equippedIt = find_if(weapons.begin(), weapons.end(),
                                [&](Weapon* weapon) { return weapon->getName() == equippedWeaponName; });

    if (equippedIt == weapons.end())
    {
        std::unique_ptr<Weapon> equippedWeapon = CreateWeaponByName(equippedWeaponName);
        if (!equippedWeapon)
        {
            cout << "Unknown weapon in save: " << equippedWeaponName << endl;
            return false;
        }

        weapons.insert(weapons.begin(), equippedWeapon.release());
        return true;
    }

    if (equippedIt != weapons.begin())
    {
        iter_swap(weapons.begin(), equippedIt);
    }
    return true;
}

MainCharacter* CreateWarriorFromGameState(const GameState& loadedState)
{
    MainCharacter* loadedWarrior = new MainCharacter(
        loadedState.playerName,
        loadedState.hp,
        loadedState.xp,
        loadedState.stamina,
        loadedState.gender,
        loadedState.coins);

    loadedWarrior->setLevel(loadedState.lvl);
    loadedWarrior->setHP(loadedState.hp);
    loadedWarrior->setXP(loadedState.xp);
    loadedWarrior->setStamina(loadedState.stamina);
    loadedWarrior->setKills(loadedState.kills);

    for (const string& weaponName : loadedState.weaponsOwnedNames)
    {
        std::unique_ptr<Weapon> weapon = CreateWeaponByName(weaponName);
        if (!weapon)
        {
            cout << "Unknown weapon in save: " << weaponName << endl;
            continue;
        }
        loadedWarrior->addWeapon(weapon.release());
    }

    for (const string& itemName : loadedState.usableItemsOwnedNames)
    {
        std::unique_ptr<UseableItems> item = CreateItemByName(itemName);
        if (!item)
        {
            cout << "Unknown item in save: " << itemName << endl;
            continue;
        }
        loadedWarrior->addUseableItems(item.release());
    }

    ReorderEquippedWeapon(loadedWarrior, loadedState.equippedWeapon);
    return loadedWarrior;
}

void ClearWarriors()
{
    for (MainCharacter* warrior : Wariors)
    {
        delete warrior;
    }
    Wariors.clear();
}

string JoinNames(const vector<string>& names)
{
    if (names.empty())
    {
        return "-";
    }

    string output;
    for (size_t i = 0; i < names.size(); ++i)
    {
        output += names[i];
        if (i + 1 < names.size())
        {
            output += ", ";
        }
    }
    return output;
}

string GetIsoTimestampNow()
{
    const time_t now = time(nullptr);
    tm timeInfo{};
#ifdef _WIN32
    localtime_s(&timeInfo, &now);
#else
    localtime_r(&now, &timeInfo);
#endif

    ostringstream out;
    out << put_time(&timeInfo, "%Y-%m-%dT%H:%M:%S");
    return out.str();
}

string BuildSlotIdFromNow()
{
    std::time_t t = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream out;
    out << "save_" << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return out.str();
}

string MakeDefaultSlotLabel(const string& isoTime)
{
    return "Save " + isoTime;
}

string FormatDisplayTime(const string& isoTime)
{
    if (isoTime.size() >= 16)
    {
        return isoTime.substr(0, 10) + " " + isoTime.substr(11, 5);
    }
    return isoTime;
}

SessionState BuildSessionStateFromParty(const int difficulty, const int battleIndex)
{
    SessionState state;
    state.mode = (Wariors.size() > 1) ? "multiplayer" : "singleplayer";
    state.partySize = static_cast<int>(Wariors.size());
    state.difficulty = difficulty;
    state.battleIndex = battleIndex;
    for (MainCharacter* warrior : Wariors)
    {
        state.party.push_back(BuildGameStateFromWarrior(warrior));
    }
    return state;
}

bool SaveSessionSlot(const string& slotId, const string& slotLabel, const string& createdAt, const int difficulty, const int battleIndex)
{
    string err;
    SessionState state = BuildSessionStateFromParty(difficulty, battleIndex);
    state.slotId = slotId;
    state.slotLabel = slotLabel.empty() ? MakeDefaultSlotLabel(GetIsoTimestampNow()) : slotLabel;
    state.createdAt = createdAt.empty() ? GetIsoTimestampNow() : createdAt;
    state.updatedAt = GetIsoTimestampNow();
    if (!SaveSession(state, slotId, &err))
    {
        ui::drawHeader("Save Failed");
        ui::centeredLine(err);
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        return false;
    }

    ui::centeredLine("Session saved to slot: " + state.slotLabel + " (" + slotId + ")");
    return true;
}

vector<string> ListSaveSlots()
{
    vector<string> slots;
    std::error_code ec;
    const std::filesystem::path saveDir("saves");
    if (!std::filesystem::exists(saveDir, ec) || ec)
    {
        return slots;
    }

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(saveDir, ec))
    {
        if (ec)
        {
            break;
        }

        if (!entry.is_regular_file())
        {
            continue;
        }

        const std::filesystem::path path = entry.path();
        if (path.extension() == ".json")
        {
            slots.push_back(path.stem().string());
        }
    }

    return slots;
}

bool IsNewSlotIdUnique(const string& slotId, const vector<string>& slots)
{
    return std::find(slots.begin(), slots.end(), slotId) == slots.end();
}

string GenerateUniqueSlotId()
{
    const vector<string> existingSlots = ListSaveSlots();
    string slotId = BuildSlotIdFromNow();
    int suffix = 1;
    while (!IsNewSlotIdUnique(slotId, existingSlots))
    {
        slotId = BuildSlotIdFromNow() + "_" + to_string(suffix++);
    }
    return slotId;
}

bool LoadSessionFromSlot(const string& slotId)
{
    SessionState loadedSession;
    string err;
    if (!LoadSession(loadedSession, slotId, &err))
    {
        ui::drawHeader("Load Failed");
        ui::centeredLine(err);
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        return false;
    }

    ClearWarriors();
    for (const GameState& playerState : loadedSession.party)
    {
        Wariors.push_back(CreateWarriorFromGameState(playerState));
    }

    numberOfCharacters = static_cast<int>(Wariors.size());
    ZZAARRIIBB = numberOfCharacters;
    gCurrentDifficulty = loadedSession.difficulty;
    gCurrentBattleIndex = loadedSession.battleIndex;

    assert(!Wariors.empty());
    if (loadedSession.mode == "multiplayer")
    {
        assert(Wariors.size() > 1);
    }

    ui::drawHeader("Load Complete");
    ui::centeredLine("Loaded session slot: " + loadedSession.slotLabel + " (" + loadedSession.slotId + ")");
    vector<string> loadedNames;
    for (MainCharacter* warrior : Wariors)
    {
        loadedNames.push_back(warrior->getName());
    }
    ui::centeredLine("Party size: " + to_string(Wariors.size()));
    ui::centeredLine("Players: " + JoinNames(loadedNames));
    ui::drawFooter("Press enter to continue");
    waitForEnterToContinue();
    return true;
}

bool ShowLoadGameMenu()
{
    const vector<string> slots = ListSaveSlots();
    if (slots.empty())
    {
        ui::drawHeader("Load Game");
        ui::centeredLine("Save not found");
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        return false;
    }

    vector<SessionSlotPreview> sessionSlots;
    vector<SessionSlotPreview> legacySlots;
    vector<SessionSlotPreview> corruptSlots;

    for (const string& slotName : slots)
    {
        SessionSlotPreview preview;
        string err;
        LoadSessionPreview(preview, slotName, &err);

        if (preview.isCurrentSlot)
        {
            sessionSlots.push_back(preview);
        }
        else if (preview.isLegacy)
        {
            legacySlots.push_back(preview);
        }
        else if (preview.isCorrupt)
        {
            corruptSlots.push_back(preview);
        }
    }

    sort(sessionSlots.begin(), sessionSlots.end(), [](const SessionSlotPreview& a, const SessionSlotPreview& b) {
        return a.updatedAt > b.updatedAt;
    });

    if (sessionSlots.empty() && legacySlots.empty())
    {
        ui::drawHeader("Load Game");
        ui::centeredLine("No loadable saves found");
        for (const SessionSlotPreview& corrupt : corruptSlots)
        {
            ui::centeredLine(corrupt.slotId + " (corrupt save)");
        }
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        return false;
    }

    ui::drawHeader("Load Game");
    for (std::size_t i = 0; i < sessionSlots.size(); ++i)
    {
        ui::centeredLine("[" + to_string(i + 1) + "] " + sessionSlots[i].slotLabel + "  (updated: " + FormatDisplayTime(sessionSlots[i].updatedAt) + ")  Party: " + JoinNames(sessionSlots[i].partyPreview));
    }
    if (!legacySlots.empty())
    {
        ui::drawDivider('-');
        ui::centeredLine("Legacy saves");
        for (std::size_t i = 0; i < legacySlots.size(); ++i)
        {
            ui::centeredLine("[" + to_string(sessionSlots.size() + i + 1) + "] " + legacySlots[i].slotId + " (migrate)");
        }
    }
    if (!corruptSlots.empty())
    {
        ui::drawDivider('-');
        for (const SessionSlotPreview& corrupt : corruptSlots)
        {
            ui::centeredLine(corrupt.slotId + " (corrupt save)");
        }
    }
    ui::drawFooter("Select a save slot");

    const int maxChoice = static_cast<int>(sessionSlots.size() + legacySlots.size());
    int choice = ui::readIntInRange(ui::centeredText("Slot [1-" + to_string(maxChoice) + "]: "), 1, maxChoice);
    if (choice <= static_cast<int>(sessionSlots.size()))
    {
        return LoadSessionFromSlot(sessionSlots[static_cast<std::size_t>(choice - 1)].slotId);
    }

    const SessionSlotPreview& legacyChoice = legacySlots[static_cast<std::size_t>(choice - static_cast<int>(sessionSlots.size()) - 1)];
    const string newSlotId = GenerateUniqueSlotId();
    const string createdAt = GetIsoTimestampNow();
    SessionState migrated;
    string loadErr;
    if (LoadSession(migrated, legacyChoice.slotId, &loadErr))
    {
        // no-op
    }
    else
    {
        GameState legacyGame;
        if (!LoadGame(legacyGame, legacyChoice.slotId, &loadErr))
        {
            ui::drawHeader("Migration Failed");
            ui::centeredLine(loadErr);
            ui::drawFooter("Press enter to continue");
            waitForEnterToContinue();
            return false;
        }

        migrated.party.push_back(legacyGame);
        migrated.partySize = 1;
        migrated.mode = "singleplayer";
    }

    migrated.version = 3;
    migrated.slotId = newSlotId;
    migrated.slotLabel = legacyChoice.slotId + " (migrated)";
    migrated.createdAt = createdAt;
    migrated.updatedAt = createdAt;
    string saveErr;
    if (!SaveSession(migrated, newSlotId, &saveErr))
    {
        ui::drawHeader("Migration Failed");
        ui::centeredLine(saveErr);
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        return false;
    }

    return LoadSessionFromSlot(newSlotId);
}

bool ShowSaveSessionMenu(const int difficulty, const int battleIndex)
{
    vector<SessionSlotPreview> sessionSlots;
    for (const string& slotId : ListSaveSlots())
    {
        SessionSlotPreview preview;
        string err;
        LoadSessionPreview(preview, slotId, &err);
        if (preview.isCurrentSlot)
        {
            sessionSlots.push_back(preview);
        }
    }

    sort(sessionSlots.begin(), sessionSlots.end(), [](const SessionSlotPreview& a, const SessionSlotPreview& b) {
        return a.updatedAt > b.updatedAt;
    });

    ui::drawHeader("Save Session");
    ui::centeredLine("1) Create New Save Slot");
    ui::centeredLine("2) Overwrite Existing Slot");
    ui::drawFooter("Choose save mode");
    const int modeChoice = ui::readIntInRange(ui::centeredText("Choice [1-2]: "), 1, 2);

    if (modeChoice == 1)
    {
        ui::drawHeader("Create New Save Slot");
        ui::centeredLine("Enter slot label (blank = auto label)");
        ui::drawFooter("Slot label");
        string slotLabel;
        getline(cin, slotLabel);
        const string slotId = GenerateUniqueSlotId();
        const string createdAt = GetIsoTimestampNow();
        return SaveSessionSlot(slotId, slotLabel, createdAt, difficulty, battleIndex);
    }

    if (sessionSlots.empty())
    {
        ui::drawHeader("Save Session");
        ui::centeredLine("No existing v3 slots found, creating new slot instead.");
        ui::drawFooter("Press enter to continue");
        waitForEnterToContinue();
        const string slotId = GenerateUniqueSlotId();
        const string createdAt = GetIsoTimestampNow();
        return SaveSessionSlot(slotId, "", createdAt, difficulty, battleIndex);
    }

    ui::drawHeader("Overwrite Existing Slot");
    for (std::size_t i = 0; i < sessionSlots.size(); ++i)
    {
        ui::centeredLine("[" + to_string(i + 1) + "] " + sessionSlots[i].slotLabel + "  (updated: " + FormatDisplayTime(sessionSlots[i].updatedAt) + ")");
    }
    ui::drawFooter("Select slot to overwrite");
    const int slotChoice = ui::readIntInRange(ui::centeredText("Slot [1-" + to_string(sessionSlots.size()) + "]: "), 1, static_cast<int>(sessionSlots.size()));
    const SessionSlotPreview& selected = sessionSlots[static_cast<std::size_t>(slotChoice - 1)];
    return SaveSessionSlot(selected.slotId, selected.slotLabel, selected.createdAt, difficulty, battleIndex);
}

int findEnemyLevel()
{
    int maxLVL;
    maxLVL = 1;
    int placeOfMaximum = 0;
    for(int i = 0 ; i < Wariors.size() ; i++)
    {
        if(Wariors[i]->getLevel() > maxLVL)
        {
            maxLVL = Wariors[i]->getLevel();
            placeOfMaximum = i;
        }
    }
    return placeOfMaximum;
}

//==========================================================
//=====Function for cout slowly=============================
    // void printS(string s)
    // {
    //     for(int i = 0 ; i < s.size() ; i++)
    //     {
    //         cout << s[i];
    //         Sleep(20);
    //     }
    //     cout << endl << endl;
    // }
    // void prints(string s)
    // {
    //     for(int i = 0 ; i < s.size() ; i++)
    //     {
    //         cout << s[i];
    //         Sleep(8);
    //     }
    //     cout << endl << endl;
    // }
//==========================================================

bool checkContinue()
{
    bool check = false;

    for(int i = 0 ; i < Wariors.size() ; i++)
    {
        if(Wariors[i]->getUseableItems().size() > 0)
        {
            return true;
        }
        else
        {
            for(int j = 0 ; j < Wariors[i]->getWeapons().size() ; j++)
            {
                if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[j]->getNeededStaminaPerAttack())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool checkContinueForOne(int i)
{
    if(Wariors[i]->getUseableItems().size() > 0)
    {
        return true;
    }
    for(int j = 0 ; j < Wariors[i]->getWeapons().size() ; j++)
    {
        if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[j]->getNeededStaminaPerAttack())
        {
            return true;
        }
    }
    return false;
}
int CalculateHPForHuman(int);
int CalculateSTForHuman(int);
int CalculateHPForZombie(int);
int CalculateSTforZombie(int);
int CalculateDMPAforZombie(int);

Shop* randomShopGenerator(){
    Shop* randomStore = nullptr;
    Batarang* a = nullptr;
    Blaster* b = nullptr;
    Katana* c = nullptr;
    grenade* d = nullptr;
    Egg* e = nullptr;
    WheyProtein* f = nullptr;
    KratosBlades* g = nullptr;
    EnergyDrink* h = nullptr;
    Mjolnir* I = nullptr;
    MiniGun* J = nullptr;
    RocketLauncher* k = nullptr;
    shuriken* l = nullptr;
    Spear* m = nullptr;
    XPpotion* n = nullptr;

    randomStore = new Shop;
    a = new Batarang(20 , 5 , "Batrang" , 50);
    b = new Blaster(35 , 10 , "Blaster" , 200);
    c = new Katana(20 , 15 , "Katana" , 120);
    d = new grenade(75 , 50 , "Grenade" , 150);
    e = new Egg(10 , 30 , "Egg" , 50 , 0);
    f = new WheyProtein(30 , 30 , "Whey Protein" , 75 , 0);
    g = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
    h = new EnergyDrink(60 , 0 , "Energy Drink" , 75 , 0);
    I = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
    J = new MiniGun(55 , 30 , "MiniGun" , 600 );
    k = new RocketLauncher(75 , 40 , "Rocket Launcher" , 1000);
    l = new shuriken(15 , 1 , "shuriken" , 30);
    m = new Spear(35 , 15 , "Spear" , 75);
    n = new XPpotion(0 , 0 , "XP Potion" , 25, 50);

    vector<Weapon*> wp{a, b, c, d,g, I, J, k, l, m};
    vector<UseableItems*> itms{e, f,h,n};
    srand(time(0));
    vector<Weapon*> outputweapon;
    vector<UseableItems*> outputusable;
    for(int i=0;i<10;i++){
        if(rand()%2 == 0){
            outputweapon.push_back(wp[i]);
        }
        else{
            delete wp[i];
        }
    }
    for(int i=0 ; i<4 ;i++){
        if(rand()%2 == 0){
            outputusable.push_back(itms[i]);
        }
        else{

            delete itms[i];
        }
    }
    randomStore->setWeapon(outputweapon);
    randomStore->setUsableItems(outputusable);
    return randomStore;

}


void makingNewcharacter()
{
    string name;
    int age;
    string gender;

    prints("===============Section of making your dream wariror===============");
    cout << endl;
    printS("Enter name of the Warior :");
    getline(cin , name);
    ui::clearScreen();

    printS("Enter gender of the Warior:(male - female) ");
    getline(cin , gender);
    while(gender != "male" && gender != "female")
    {
        prints("Invalid Input try again: ");
        getline(cin , gender);
    }
    ui::clearScreen();


    // Warior.setName(name);
    // Warior.setGender(gender);
    cout << endl;
    prints("===============================================");
    cout << endl;
    prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
    printS("KING Summoned you");
    printS("===This gift is given to you by the king to buy your Weapons and continue:===");
    cout << endl;
    printS("===== Here you are:" );
    cout << endl << endl;
    printS("Now you have 1000 G");
    // Warior.setGold(1000);
    // this_thread::sleep_for(chrono::seconds(33));
    ui::clearScreen();

    prints("================================================");

    printS("==========Here is the section where you should pick one glorious Permanent Weapon ==============");
    cout << endl;
    int ChosenWeapon;
    {
        printS("==Now you should pick up a powerful permanent weapon which will be with you till the end of the war :==");
        printS("plese pick up one weapon: ");
        cout << endl;

        cout << "1.Katana" << endl << "2.Blaster" << endl<<"3.Kratos Blades"<<endl<<"4.MiniGun"<<endl<<"5.Mjiolnir"<<endl<<"6.Rocket Launcher"<<endl;

        printS("Katana(120 G)(Damage : 20) (NeededStamina : 15)");
        printS("Blaster(200 G) (Damage : 35) (Needed Stamina : 10)");
        printS("Kratos Blades(150 G) (Damage : 25) (Needed Stamina : 15)");
        printS("MiniGun(600 G) (Damage : 55) (Needed Stamina : 30)");
        printS("Mjiolnir(130 G) (Damage : 25) (Needed Stamina : 20)");
        printS("Rocket Launcher(1000 G) (Damage : 75) (Needed Stamina : 40)");


        ChosenWeapon = ui::readIntInRange(ui::centeredText("Select weapon [1-6]: "), 1, 6);

        if(ChosenWeapon == 1)
        {
           Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
            // Warior.setGold(Warior.getGold()-yourkat->getPrice());
            // Warior.addWeapon(yourkat);
        }
        else if(ChosenWeapon == 2)
        {
           Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
            // Warior.setGold(Warior.getGold()-yourblast->getPrice());
            // Warior.addWeapon(yourblast);

        }
        else if(ChosenWeapon == 3)
        {
           KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
            // Warior.setGold(Warior.getGold()-yourblades->getPrice());
            // Warior.addWeapon(yourblades);

        }
        else if(ChosenWeapon == 4)
        {
           MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
            // Warior.setGold(Warior.getGold()-yourmini->getPrice());
            // Warior.addWeapon(yourmini);

        }
        else if(ChosenWeapon == 5)
        {
           Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
            // Warior.setGold(Warior.getGold()-yourmjo->getPrice());
            // Warior.addWeapon(yourmjo);

        }
        else if(ChosenWeapon == 6)
        {
           RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
            // Warior.setGold(Warior.getGold()-yourrock->getPrice());
            // Warior.addWeapon(yourrock);

        }

    }
    ui::clearScreen();
    prints("==============================================");
    cout << endl;

    printS("========================== GIFT ===========================");
    printS("===== Now we will give you somthing that you can heal yourself with and give your muscular body a litle bit of Energy.So take them and add them to your Inventory");
    printS("The first one is WheyPowder which helps you get Stamina(by 30 ST) and heal your body(by 30 HP) you will have two :");
    WheyProtein* ptr1WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
    WheyProtein* ptr2WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
    // Warior.addUseableItems(ptr1WheyPowder);
    // Warior.addUseableItems(ptr2WheyPowder);

    // Warior.setLevel(1);
    // Warior.setHP(100);
    // Warior.setStamina(100);
    // Warior.setXP(0);
    pauseForReadability(1500);
    ui::clearScreen();

}

void makingSomeNewCharacter()
{
    // ofstream user("data/users.txt" , ios::app);
    int wariorMode;
    prints("How many playable character would you like to include in the game?");
    numberOfCharacters = ui::readIntInRange(ui::centeredText("How many playable characters? [1-4]: "), 1, 4);
    ZZAARRIIBB = numberOfCharacters;
    ui::clearScreen();

    for (int w = 0; w < numberOfCharacters; w++)
    {
       while(true){
       if(numberOfCharacters>1)
            cout<<"Player "<<w+1<<"'s turn:"<<endl;

        ui::clearScreen();
        // if (wariorMode == 1)
        // {
        //    string hyhy;
        //     int n=0;
        //     while (userList >> hyhy){
        //         n++;
        //    }
        //    if(n!=0){
        //    	cout << "\nlist of users:\n";
        //        string username;

        //         userList.close();
        //         ifstream userList("data/users.txt");
        //        while (userList >> username)
        //            cout << username << endl;
        //        prints("Enter the name of the warior you'd like to choose:\n");
        //        string insideWarior;
        //        cin >> insideWarior;
        //        ifstream wariorDetail ("data/" + insideWarior + ".txt");
        //        string wariorName, wariorGender;
        //        int wariorHP, wariorXP, wariorStamina, wariorGold, wariorLevel, wariorKills, weaponNum, usableNum;
        //        wariorDetail >> wariorName >> wariorGender >> wariorHP >> wariorXP >> wariorGold >> wariorStamina >> wariorLevel >> wariorKills >> weaponNum >> usableNum;
        //        MainCharacter* newWarior = new MainCharacter(wariorName , wariorHP , wariorXP , wariorStamina , wariorGender , wariorGold);
        //        newWarior->setKills(wariorKills);
        //        newWarior->setLevel(wariorLevel);
        //        int o = 1;
        //        string itemTemp = "!";
        //        while (wariorDetail >> itemTemp)
        //        {
        //            for (int n = 0; n < weaponNum; n++)
        //            {
        //                 if(itemTemp == "Katana")
        //                 {
        //                    Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
        //                     newWarior->addWeapon(yourkat);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Blaster")
        //                 {
        //                    Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
        //                     newWarior->addWeapon(yourblast);
        //                     break;

        //                 }
        //                 else if(itemTemp == "Kratos")
        //                 {
        //                    KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
        //                     newWarior->addWeapon(yourblades);
        //                     break;
        //                 }
        //                 else if(itemTemp == "MiniGun")
        //                 {
        //                    MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
        //                     newWarior->addWeapon(yourmini);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Mjolnir")
        //                 {
        //                    Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
        //                     newWarior->addWeapon(yourmjo);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Rocket")
        //                 {
        //                    RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
        //                     newWarior->addWeapon(yourrock);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Spear")
        //                 {
        //                    Spear* yourspear = new Spear(35 , 15 , "Spear" , 75);
        //                     newWarior->addWeapon(yourspear);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Batarang")
        //                 {
        //                    Batarang* yourbat = new Batarang(20 , 5 , "Batrang" , 50);
        //                     newWarior->addWeapon(yourbat);
        //                     break;
        //                 }
        //                 else if(itemTemp == "Grenade")
        //                 {
        //                    grenade* yournade = new grenade(75 , 50 , "Grenade" , 150);
        //                     newWarior->addWeapon(yournade);
        //                     break;
        //                 }
        //                 else if(itemTemp == "shuriken")
        //                 {
        //                    shuriken* yourshur = new shuriken(15 , 1 , "shuriken" , 30);
        //                     newWarior->addWeapon(yourshur);
        //                     break;
        //                 }
        //                 else if (itemTemp == "Launcher" || itemTemp == "Blades")
        //                 {
        //                     continue;
        //                 }

        //                 // newWarior->showCharacterWeapons();
        //            }
        //         for (int n = 0; n < usableNum; n++)
        //         {
        //             if(itemTemp == "Egg")
        //             {
        //                Egg* youregg = new Egg(10 , 30 , "Egg" , 50 , 0);
        //                 newWarior->addUseableItems(youregg);
        //                 break;
        //             }
        //             else if(itemTemp == "Whey")
        //             {
        //                WheyProtein* yourwhey = new WheyProtein(30 , 30 , "Whey Protein" , 75 , 0);
        //                 newWarior->addUseableItems(yourwhey);
        //                 break;
        //             }
        //             else if(itemTemp == "Energy")
        //             {
        //                EnergyDrink* yourenergy = new EnergyDrink(60 , 0 , "Energy Drink" , 75 , 0);
        //                 newWarior->addUseableItems(yourenergy);
        //                 break;
        //             }
        //             else if(itemTemp == "XP")
        //             {
        //                XPpotion* yourxp = new XPpotion(0 , 0 , "XP Potion" , 25, 50);
        //                 newWarior->addUseableItems(yourxp);
        //                 break;
        //             }
        //             else if (itemTemp == "Potion" || itemTemp == "Drink" || itemTemp == "Protein")
        //             {
        //                 continue;
        //             }

        //         }
        //           Wariors.push_back(newWarior);
        //        break;
        //     }

        //    }
        //    else{
        //    	prints("There are no available wariors saved on your memory!\nYou'll have to make one!");
        //    }

        // }


//           cout << endl;
//       	prints("===============================================");
//       	cout << endl;
//       	prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
//       	this_thread::sleep_for(chrono::seconds(33));
//       	ui::clearScreen();
            int age;
            string gender , name;

            prints("===============making your dreamy warrior===============");
            cout << endl;
            cout << "Enter the name of your Warior" << endl;

            cin >> name;
            // cout << name;
            // user << name << endl;
            ui::clearScreen();

            printS("Enter gender of the Warior:(male - female) ");
            getline(cin >>ws, gender);
            while(gender != "male" && gender != "female")
            {
                prints("Invalid Input try again: ");
                getline(cin>>ws , gender);
            }
            ui::clearScreen();

            cout << endl;
            prints("===============================================");
            cout << endl;
            printS("KING Summoned you");
           printS("===This gift is given to you by the king to buy your Weapons and continue:===");
           cout << endl;
           printS("===== Here you are:" );
            prints("Your Character will have 1000 G at the begining");
            pauseForReadability(1000);
            ui::clearScreen();

            MainCharacter* newWarior = new MainCharacter(name , 100 , 0 , 100 , gender , 1000);
            newWarior->setKills(0);
            newWarior->setLevel(1);
            newWarior->setXP(0);
            printS("==========Here is the section where you should pick one glorious Permanent Weapon==============");
            cout << endl;
            int ChosenWeapon;
        {
            printS("==Now you should pick up a powerful permanent weapon which will be with you till the end of the war :==");
            printS("plese pick up one weapon: ");
            cout << endl;

            cout << "1.Katana" << endl << "2.Blaster" << endl<<"3.Kratos Blades"<<endl<<"4.MiniGun"<<endl<<"5.Mjiolnir"<<endl<<"6.Rocket Launcher"<<endl;

            printS("Katana(120 G)(Damage : 20) (NeededStamina : 15)");
            printS("Blaster(200 G) (Damage : 35) (Needed Stamina : 10)");
            printS("Kratos Blades(150 G) (Damage : 25) (Needed Stamina : 15)");
            printS("MiniGun(600 G) (Damage : 55) (Needed Stamina : 30)");
            printS("Mjiolnir(130 G) (Damage : 25) (Needed Stamina : 20)");
            printS("Rocket Launcher(1000 G) (Damage : 75) (Needed Stamina : 40)");


            ChosenWeapon = ui::readIntInRange(ui::centeredText("Select weapon [1-6]: "), 1, 6);

            if(ChosenWeapon == 1)
            {
               Katana* yourkat = new Katana(20 , 15 , "Katana" , 120);
                newWarior->setGold(newWarior->getGold()-yourkat->getPrice());
                newWarior->addWeapon(yourkat);
            }
            else if(ChosenWeapon == 2)
            {
               Blaster* yourblast = new Blaster(35 , 10 , "Blaster" , 200);
                newWarior->setGold(newWarior->getGold()-yourblast->getPrice());
                newWarior->addWeapon(yourblast);

            }
            else if(ChosenWeapon == 3)
            {
               KratosBlades* yourblades = new KratosBlades(25 , 15 , "Kratos Blades" , 150 );
                newWarior->setGold(newWarior->getGold()-yourblades->getPrice());
                newWarior->addWeapon(yourblades);

            }
            else if(ChosenWeapon == 4)
            {
               MiniGun* yourmini = new MiniGun(55 , 30 , "MiniGun" , 600 );
                newWarior->setGold(newWarior->getGold()-yourmini->getPrice());
                newWarior->addWeapon(yourmini);

            }
            else if(ChosenWeapon == 5)
            {
               Mjolnir* yourmjo = new Mjolnir(25 , 20 , "Mjolnir" , 130 );
                newWarior->setGold(newWarior->getGold()-yourmjo->getPrice());
                newWarior->addWeapon(yourmjo);

            }
            else if(ChosenWeapon == 6)
            {
               RocketLauncher* yourrock = new RocketLauncher(110 , 40 , "Rocket Launcher" , 1000);
                newWarior->setGold(newWarior->getGold()-yourrock->getPrice());
                newWarior->addWeapon(yourrock);

            }

            }
            ui::clearScreen();

            printS("========================== GIFT ===========================");
           printS("===== Now we will give you somthing that you can heal yourself with and give your muscular body a litle bit of Energy.So take them and add them to your Inventory");
           printS("The first one is Whey Powder which helps you get Stamina(by 30 ST) and heal your body(by 30 HP) you will have two :");
            prints("Here are two whey powders for you");

            WheyProtein* ptr1WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
            WheyProtein* ptr2WheyPowder = new WheyProtein(30 , 30   , "Whey Protein" , 75, 0);
            newWarior->addUseableItems(ptr1WheyPowder);
            newWarior->addUseableItems(ptr2WheyPowder);
            pauseForReadability(900);
            ui::clearScreen();
            Wariors.push_back(newWarior);

           break;



        }

    }

}
//Making Game ready to Start the story
// void makeGameplayReady()
// {
// //    Store.setLevel(1);
// //    Store.setName("BlackMarket");
//     Enemyhouse.setEnemyLevel();

// }

//if return value was 1 MainCharacter goes shopping if return value was 0 MainCharacter fights ;
bool randomShuffle ( int Difficulty , int Level ) {
    srand(time(0)) ;
    vector<int> shuffle ;
    int random ;
    if (Difficulty == 1) {
        random = ((rand() % 100) / Level) - (Level%10) + 35 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(shuffle.begin(), shuffle.end(), rng);
        // random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            cout << "Go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
    if (Difficulty == 2) {
        random = ((rand() % 100) / Level) - (Level%10) + 25 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(shuffle.begin(), shuffle.end(), rng);
        // random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            cout << "go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
    if (Difficulty == 3) {
        random = ((rand() % 100) / Level) - (Level%10) + 15 ;
        if (random>=100 ){
            random = 90 ;
        }
        if (random<=0 ){
            random = 10 ;
        }
        for (int i=0 ; i<random ; ++i){
            shuffle.push_back(1);
        }
        for (int i=0 ; i<100-shuffle.size() ; ++i){
            shuffle.push_back(0);
        }
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(shuffle.begin(), shuffle.end(), rng);
        // random_shuffle(shuffle.begin() , shuffle.end());
        if (shuffle[0] == 1){
            //cout << "go to shop" << endl ;
            return 1 ;
        }
        if (shuffle[0] == 0){
            //cout << "FIGHT" << endl ;
            return 0 ;
        }
        shuffle.clear() ;
        shuffle.shrink_to_fit();
    }
    return -1;
}

bool isAlive()
{
    for(MainCharacter* warrior : Wariors)
    {
        if(warrior != nullptr && warrior->getHP() > 0)
        {
            return true;
        }
    }
    return false;
}

int findRandomAliveWarriorIndex()
{
    vector<int> aliveIndices;
    aliveIndices.reserve(Wariors.size());

    for(int i = 0; i < static_cast<int>(Wariors.size()); ++i)
    {
        if(Wariors[i] != nullptr && Wariors[i]->getHP() > 0)
        {
            aliveIndices.push_back(i);
        }
    }

    if(aliveIndices.empty())
    {
        return -1;
    }

    return aliveIndices[static_cast<std::size_t>(rand() % aliveIndices.size())];
}


int main()
{
    try
    {

    // string tttt;
    // userList >> tttt;
    // cout << tttt << endl;
    cout << endl;
    prints("===============================================");
    cout << endl;
      prints("The worlds are colliding...parallel realities and dimensions are merging into one,causing a disaster! monsters and evil forces from corrupt universes are invading our realm and wish to conquer it!Even some former allies are taking advantage of the current situation and have joined the dark side in order to take over our world! You and your few comrades are  the empire's last hope...The king needs you to defend the kingdom and save your people from these hellish creatures.    thankfully, you'll have access to different kinds of weapons from all universes which will ease your crusade.");
      // this_thread::sleep_for(chrono::seconds(33));
    ui::clearScreen();
    Enemy* enemy = nullptr;

    ui::drawHeader("Main Menu");
    ui::centeredLine("1) New Game");
    ui::centeredLine("2) Load Game");
    ui::drawFooter("Choose option [1-2]");
    int mainMenuChoice = ui::readIntInRange(ui::centeredText("> "), 1, 2);
    ui::clearScreen();

    bool loadedFromSlot = false;
    if (mainMenuChoice == 2)
    {
        loadedFromSlot = ShowLoadGameMenu();
        if (!loadedFromSlot)
        {
            ui::drawHeader("Fallback to New Game");
            ui::centeredLine("Starting a new game setup.");
            ui::drawFooter("Press enter to continue");
            waitForEnterToContinue();
            makingSomeNewCharacter();
        }
    }
    else
    {
        makingSomeNewCharacter();
    }

    assert(!Wariors.empty());
    if (Wariors.size() > 1)
    {
        assert(static_cast<int>(Wariors.size()) > 1);
    }

    EnemyFactory Enemyhouse(Wariors[findEnemyLevel()] , ZZAARRIIBB);
    int Difficulty = gCurrentDifficulty;
    int enemyCount = gCurrentBattleIndex;

    if (!loadedFromSlot)
    {
        ui::drawHeader("Difficulty Selection");
        ui::centeredLine("  1) Casual");
        ui::centeredLine("  2) Challenger");
        ui::centeredLine("  3) Nightmare");
        ui::drawFooter("Choose difficulty [1-3]");
        Difficulty = ui::readIntInRange(ui::centeredText("> "), 1, 3);
        ui::clearScreen();
    }
    gCurrentDifficulty = Difficulty;

    bool checkStatus;

    bool playerRequestedQuit = false;

    while(!playerRequestedQuit && isAlive() && checkContinue())
    {
       checkStatus = randomShuffle(Difficulty , Wariors[findEnemyLevel()]->getLevel());

       if(checkStatus)
       {
        DBG_LOG("Menu transition: battle -> shop");


        for(int i = 0 ; i < Wariors.size() ; i++)
        {
            if(Wariors[i]->getHP() > 0)
            {
                Store = randomShopGenerator();
                prints("=========================================");
                ui::centeredLine("Buying item for " + Wariors[i]->getName());
                prints("=========================================");
                Store->BuyItem(Wariors[i]);
                // userSave (Wariors[i]->getName(), Wariors[i]->getGender(), Wariors[i]->getHP(), Wariors[i]->getXP(), Wariors[i]->getGold(), Wariors[i]->getStamina(), Wariors[i]->getLevel(), Wariors[i]->getKills(), Wariors[i]->getWeapons().size(), Wariors[i]->getUseableItems().size() , Wariors[i]->getWeapons(), Wariors[i]->getUseableItems());
                delete Store;
            }

        }

       }

       else
       {
        int whichEnemy = rand()%2;
        if(whichEnemy == 0)
        {
            enemy = Enemyhouse.makeZombie();
        }
        else if(whichEnemy == 1)
        {
            enemy = Enemyhouse.makeHuman();
        }
        DBG_LOG("Enemy created: " << enemy->getEnemyModel()->getName() << " hp=" << enemy->getEnemyModel()->getHP() << " st=" << enemy->getEnemyModel()->getStamina());
        enemyCount++;
        gCurrentBattleIndex = enemyCount;
        bool enemyDefeated = false;

        DBG_LOG("Entering battle loop for enemy #" << enemyCount);

        while(!enemyDefeated && enemy->getEnemyModel()->getHP() > 0 && isAlive() && checkContinue())
        {
            for(int i = 0 ; i < Wariors.size() && !enemyDefeated && enemy->getEnemyModel()->getHP() > 0 ; i++)
            {
                if(Wariors[i]->getHP() > 0)
                {
                    if(checkContinueForOne(i))
                    {
                pauseForReadability();
                       ui::clearScreen();
                        ui::drawHeader("Battlefield");
                        ui::centeredLine("Level " + to_string(Wariors[findEnemyLevel()]->getLevel()) + " encounter");
                        ui::centeredLine("Enemy #" + to_string(enemyCount) + " race:");
                        if(enemy->getEnemyModel()->getName() == "Human")
                        {
                            ui::centeredLine("Human");
                        }
                        else if(enemy->getEnemyModel()->getName() == "Zombie")
                        {
                            ui::centeredLine("Zombie");
                        }

                        ui::drawDivider('-');
                        ui::centeredLine(Wariors[i]->getName() + "'s turn");
                        ui::drawDivider('-');
                        ui::centeredLine("Facing Enemy #" + to_string(enemyCount));
                        ui::centeredLine("1) Fight");
                        ui::centeredLine("2) Use inventory");
                        ui::centeredLine("3) Save and quit");
                        uiBattleStatus(Wariors[i], enemy);
                        ui::drawFooter("Choose action");

                        int input = ui::readIntInRange(ui::centeredText("Your choice [1-3]: "), 1, 3);

                        if(input == 1)
                        {
                            ui::clearScreen();
                            while(true)
                            {
                                ui::drawHeader("Choose a Weapon");
                                ui::centeredLine("For " + Wariors[i]->getName() + " (0 to go back)");
                                ui::drawDivider('-');
                                Wariors[i]->showCharacterWeapons();
                                ui::drawFooter("Select weapon number (0 to go back)");
                                input = ui::readIntInRange(ui::centeredText("Weapon number: "), 0, static_cast<int>(Wariors[i]->getWeapons().size()));

                                if(input <= Wariors[i]->getWeapons().size() && input >= 1)
                                {
                                    if(Wariors[i]->getStamina() > Wariors[i]->getWeapons()[input-1]->getNeededStaminaPerAttack())
                                    {
                                        Wariors[i]->Attack(enemy , Wariors[i]->getWeapons()[input-1]);
                                        if(enemy->getEnemyModel()->getHP() <= 0)
                                        {
                                            Wariors[i]->setKills(Wariors[i]->getKills() + 1);
                                            prints("===========================================");
                                            ui::centeredLine("Enemy #" + to_string(enemyCount) + " was killed by " + Wariors[i]->getName() + " | " + to_string(Wariors[i]->getKills()) + " total kill(s)");
                                            prints("===========================================");
                                            pauseForReadability();
                                           ui::clearScreen();
                                            // for (int l = 0; l < Wariors.size(); l++)
                                            // {
                                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                                            // }

                                            Wariors[i]->setGold(Wariors[i]->getGold() + 70);
                                            Wariors[i]->setXP(Wariors[i]->getXP() + 150);
                                            const int beforeLevel = Wariors[i]->getLevel();
                                            Wariors[i]->CalculateLevel();
                                            DBG_LOG("XP gained: " << Wariors[i]->getName() << " +150 xp=" << Wariors[i]->getXP() << " level " << beforeLevel << "->" << Wariors[i]->getLevel());
                                            for(int j = 0 ; j < Wariors.size() ; j++)
                                            {
                                                if(j != i)
                                                {
                                                    Wariors[j]->setXP(Wariors[j]->getXP() + 40);
                                                    Wariors[j]->setGold(Wariors[j]->getGold() + 30);
                                                    const int allyBeforeLevel = Wariors[j]->getLevel();
                                                    Wariors[j]->CalculateLevel();
                                                    DBG_LOG("XP gained: " << Wariors[j]->getName() << " +40 xp=" << Wariors[j]->getXP() << " level " << allyBeforeLevel << "->" << Wariors[j]->getLevel());
                                                }
                                            }
                                            if(enemy->getEnemyModel()->getName() == "Human")
                                            {
                                               ui::clearScreen();
                                                cout << "==========================" << endl;
                                                cout << "Inventory Of Enemy Looted" << endl;
                                                cout << "==========================" << endl;
                                                pauseForReadability(1000);
                                               ui::clearScreen();
                                                Wariors[i]->getEnemyUseableItems(enemy->getEnemyModel()->getEnemyUseableItems());
                                                Wariors[i]->getEnemyWeapons(enemy->getEnemyModel()->getEnemyWeapons());
                                            //     for (int l = 0; l < Wariors.size(); l++)
                                            // {
                                            //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
                                            // }

                                            }
                                            enemyDefeated = true;
                                            DBG_LOG("Enemy defeated: #" << enemyCount << ", transitioning to post-battle menu");
                                            break;
                                        }

                                        break;
                                    }
                                    else
                                    {
                                        prints("   Your character doesn't have enough energy to use this weapon");
                                    }
                                }
                                else if(input == 0)
                                {
                                    i--;
                                    break;
                                }

                            }
                        }

                        else if(input == 2)
                        {
                            ui::clearScreen();
                            while(true)
                            {
                                ui::drawHeader("Use Inventory Item");
                                ui::centeredLine("For " + Wariors[i]->getName() + " (0 to go back)");
                                ui::drawDivider('-');
                                Wariors[i]->showCharacterUsableItems();
                                ui::drawFooter("Select item number (0 to go back)");
                                input = ui::readIntInRange(ui::centeredText("Item number: "), 0, static_cast<int>(Wariors[i]->getUseableItems().size()));

                                if(input >= 1 && input <= Wariors[i]->getUseableItems().size())
                                {
                                    Wariors[i]->useItem(input);
                                    DBG_LOG("Inventory used by " << Wariors[i]->getName() << " | hp=" << Wariors[i]->getHP() << " st=" << Wariors[i]->getStamina() << " xp=" << Wariors[i]->getXP() << " lvl=" << Wariors[i]->getLevel());
                                    i--;

                                    break;
                                }
                                else if(input == 0)
                                {
                                    i--;
                                    break;
                                }
                            }
                        }
                        else if (input == 3)
                        {
                            const bool saveSucceeded = ShowSaveSessionMenu(gCurrentDifficulty, gCurrentBattleIndex);
                            DBG_LOG("Menu transition: battle -> save+quit");
                            if(saveSucceeded)
                            {
                                playerRequestedQuit = true;
                                break;
                            }

                            continue;
                        }

                        if(enemyDefeated)
                        {
                            break;
                        }

                    }
                    else
                    {
                        ui::centeredLine(Wariors[i]->getName() + " couldn't attack due to lack of stamina");


                    }
                }
            }

            if(playerRequestedQuit || enemyDefeated)
            {
                break;
            }

             if(!playerRequestedQuit && enemy->getEnemyModel()->getHP() > 0)
            {
                for(int attacksThisTurn = 0; attacksThisTurn < 2 && isAlive() && enemy->getEnemyModel()->getHP() > 0; ++attacksThisTurn)
                {
                    const int attackNumber = findRandomAliveWarriorIndex();
                    if(attackNumber < 0)
                    {
                        break;
                    }

                    ui::ResetCombatLogState();
                    const int hpBeforeAttack = Wariors[attackNumber]->getHP();
                    enemy->getEnemyController()->Attack(Wariors[attackNumber]);

                    if(!ui::DidLogAttackThisTurn())
                    {
                        const int hpAfterAttack = Wariors[attackNumber]->getHP();
                        ui::LogAttack(
                            enemy->getEnemyModel()->getName(),
                            Wariors[attackNumber]->getName(),
                            "Enemy Attack",
                            0,
                            0,
                            0,
                            hpBeforeAttack,
                            hpAfterAttack);
                        ui::centeredLine("Enemy action could not deal damage this turn.");
                    }

                    ui::WaitForKey("Press Enter to continue...");

                    if(Wariors[attackNumber]->getHP() <= 0)
                    {
                        Wariors[attackNumber]->setHP(0);
                        prints("==================================");
                        cout << "       " << Wariors[attackNumber]->getName() << " is dead" << endl;
                        prints("==================================");
                        delete Wariors[attackNumber];
                        Wariors.erase(Wariors.begin() + attackNumber);
                    }
                }
            }


        }

        DBG_LOG("Exiting battle loop for enemy #" << enemyCount);
        DBG_LOG("Enemy deleted: #" << enemyCount);

        delete enemy;
        enemy = nullptr;

       }
    }

    if(playerRequestedQuit)
    {
        prints("=============================================");
        ui::centeredLine("Game saved. Exiting safely.");
        prints("=============================================");
    }
    else
    {
        prints("=============================================");
        ui::centeredLine("All warriors have fallen.");
        prints("=============================================");
    }
    // for (int l = 0; l < Wariors.size(); l++)
    // {
    //     userSave (Wariors[l]->getName(), Wariors[l]->getGender(), Wariors[l]->getHP(), Wariors[l]->getXP(), Wariors[l]->getGold(), Wariors[l]->getStamina(), Wariors[l]->getLevel(), Wariors[l]->getKills(), Wariors[l]->getWeapons().size(), Wariors[l]->getUseableItems().size() , Wariors[l]->getWeapons(), Wariors[l]->getUseableItems());
    // }
    }
    catch(const std::exception& ex)
    {
        ui::drawHeader("Input Error");
        ui::centeredLine(ex.what());
        ui::drawFooter("Exiting game safely");
        return 1;
    }
}

int CalculateHPForHuman(int level)
{
    return level*8 + 80;
}
int CalculateSTForHuman(int level)
{
    return level *10 + 70;
}

int CalculateDMPAforZombie(int level)
{
    int DMPA;
    DMPA = static_cast<int>(pow(level , 10.0 / 7.0) + 10);
    return DMPA;
}
int CalculateSTforZombie(int level)
{
    int ST;
    ST = level * 20 + 50;
    return ST;
}
int CalculateHPForZombie(int level)
{
    int HP;
    HP = static_cast<int>(pow(level , 4.0 / 3.0) * 20 + 50);
    return HP;
}
