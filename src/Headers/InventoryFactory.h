#pragma once

#include <memory>
#include <string>

class Weapon;
class UseableItems;

std::unique_ptr<Weapon> CreateWeaponByName(const std::string& name);
std::unique_ptr<UseableItems> CreateItemByName(const std::string& name);
