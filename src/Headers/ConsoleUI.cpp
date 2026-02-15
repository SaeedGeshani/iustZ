#include "ConsoleUI.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>

namespace ui
{
namespace
{
bool g_loggedAttackThisTurn = false;
}

std::string centeredText(const std::string& text, int width)
{
    if(static_cast<int>(text.size()) >= width)
    {
        return text;
    }

    int padding = (width - static_cast<int>(text.size())) / 2;
    return std::string(padding, ' ') + text;
}

void centeredLine(const std::string& text, int width)
{
    std::cout << centeredText(text, width) << std::endl;
}

void drawDivider(char fill, int width)
{
    centeredLine(std::string(width, fill));
}

void drawHeader(const std::string& title)
{
    drawDivider('=');
    centeredLine(" " + title);
    drawDivider('=');
}

void drawFooter(const std::string& hint)
{
    drawDivider('-');
    centeredLine(hint);
}

int readIntInRange(const std::string& prompt, int lo, int hi)
{
    if(lo > hi)
    {
        throw std::invalid_argument("readIntInRange called with invalid bounds");
    }

    while(true)
    {
        std::cout << prompt;
        int value;

        if(std::cin >> value)
        {
            if(value >= lo && value <= hi)
            {
                return value;
            }
            centeredLine("Please enter a number between " + std::to_string(lo) + " and " + std::to_string(hi) + ".");
        }
        else
        {
            if(std::cin.eof())
            {
                throw std::runtime_error("Input stream closed while waiting for numeric input");
            }

            centeredLine("Please enter a valid number.");
            std::cin.clear();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void WaitForKey(const std::string& prompt)
{
    centeredLine(prompt);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void LogAttack(
    const std::string& attackerName,
    const std::string& defenderName,
    const std::string& attackLabel,
    int baseDamage,
    int defenseValue,
    int finalDamage,
    int hpBefore,
    int hpAfter)
{
    g_loggedAttackThisTurn = true;

    drawDivider('=', 64);
    centeredLine(attackerName + " attacks " + defenderName + " with " + attackLabel + "!");
    centeredLine("Damage: base " + std::to_string(baseDamage) + " - defense " + std::to_string(defenseValue) + " = " + std::to_string(finalDamage));

    if(finalDamage <= 0)
    {
        centeredLine("No damage dealt.");
    }
    else
    {
        centeredLine(defenderName + " took " + std::to_string(finalDamage) + " damage. HP: " + std::to_string(hpBefore) + " -> " + std::to_string(hpAfter));
    }

    drawDivider('=', 64);
}

void ResetCombatLogState()
{
    g_loggedAttackThisTurn = false;
}

bool DidLogAttackThisTurn()
{
    return g_loggedAttackThisTurn;
}
}
