#include "DepthStriderEnchantment.h"

DepthStriderEnchantment::DepthStriderEnchantment(int id, int frequency) : Enchantment(id, frequency, EnchantmentCategory::armor_feet)
{
    setDescriptionId(IDS_ENCHANTMENT_WATER_WALKER);
}

int DepthStriderEnchantment::getMinCost(int level)
{
    return 1 + (level - 1) * 10;
}

int DepthStriderEnchantment::getMaxCost(int level)
{
    return getMinCost(level) + 15;
}

int DepthStriderEnchantment::getMaxLevel()
{
    return 3;
}