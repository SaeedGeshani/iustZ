#include "EnemyStats.h"

#include <cmath>

int CalculateHPForHuman(int level)
{
    return level * 8 + 80;
}

int CalculateSTForHuman(int level)
{
    return level * 10 + 70;
}

int CalculateDMPAforZombie(int level)
{
    return static_cast<int>(std::pow(level, 10.0 / 7.0) + 10);
}

int CalculateSTforZombie(int level)
{
    return level * 20 + 50;
}

int CalculateHPForZombie(int level)
{
    return static_cast<int>(std::pow(level, 4.0 / 3.0) * 20 + 50);
}
