#include "InventoryFactory.h"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Batarang.h"
#include "Blaster.h"
#include "Egg.h"
#include "EnergyDrink.h"
#include "Katana.h"
#include "KratosBlades.h"
#include "MiniGun.h"
#include "Mjolnir.h"
#include "RocketLauncher.h"
#include "Spear.h"
#include "UseableItems.h"
#include "Weapon.h"
#include "WheyProtein.h"
#include "XPpotion.h"
#include "grenade.h"
#include "shuriken.h"

std::unique_ptr<Weapon> CreateWeaponByName(const std::string& name)
{
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Weapon>()>> weaponFactory = {
        {"Katana", []() { return std::make_unique<Katana>(20, 15, "Katana", 120); }},
        {"Blaster", []() { return std::make_unique<Blaster>(35, 10, "Blaster", 200); }},
        {"Kratos Blades", []() { return std::make_unique<KratosBlades>(25, 15, "Kratos Blades", 150); }},
        {"MiniGun", []() { return std::make_unique<MiniGun>(55, 30, "MiniGun", 600); }},
        {"Mjolnir", []() { return std::make_unique<Mjolnir>(25, 20, "Mjolnir", 130); }},
        {"Rocket Launcher", []() { return std::make_unique<RocketLauncher>(75, 40, "Rocket Launcher", 1000); }},
        {"Batrang", []() { return std::make_unique<Batarang>(20, 5, "Batrang", 50); }},
        {"Grenade", []() { return std::make_unique<grenade>(75, 50, "Grenade", 150); }},
        {"shuriken", []() { return std::make_unique<shuriken>(15, 1, "shuriken", 30); }},
        {"Spear", []() { return std::make_unique<Spear>(35, 15, "Spear", 75); }}
    };

    const auto it = weaponFactory.find(name);
    if (it == weaponFactory.end())
    {
        return nullptr;
    }

    return it->second();
}

std::unique_ptr<UseableItems> CreateItemByName(const std::string& name)
{
    static const std::unordered_map<std::string, std::function<std::unique_ptr<UseableItems>()>> itemFactory = {
        {"Egg", []() { return std::make_unique<Egg>(10, 30, "Egg", 50, 0); }},
        {"Whey Protein", []() { return std::make_unique<WheyProtein>(30, 30, "Whey Protein", 75, 0); }},
        {"Energy Drink", []() { return std::make_unique<EnergyDrink>(60, 0, "Energy Drink", 75, 0); }},
        {"XP Potion", []() { return std::make_unique<XPpotion>(0, 0, "XP Potion", 25, 50); }},
        {"XPpotion", []() { return std::make_unique<XPpotion>(0, 0, "XP Potion", 25, 50); }}
    };

    const auto it = itemFactory.find(name);
    if (it == itemFactory.end())
    {
        return nullptr;
    }

    return it->second();
}
